#include <mutex>
#include <queue>

template<typename T>
class Pool {
public:
    Pool(int cap): _capacity(cap) {};
    ~Pool() {};
    void consume(T* t) {
        std::unique_lock<std::mutex> guard(_mtx);
        _not_empty.wait(guard, [&] {return _pool.size() > 0;});
        *t = _pool.front();
        _pool.pop_front();
        guard.unlock();
        _not_full.notify_one();
    }

    void produce(const T& t) {
        std::unique_lock<std::mutex> guard(_mtx);        
        _not_full.wait(guard, [&] {return _pool.size() < _capacity;});
        _pool.push_back(t);
        guard.unlock();
        _not_empty.notify_one();
    }
private:
    uint32_t _capacity;
    std::queue<T> _data;
    std::mutex _mtx;
    std::condition_variable _not_empty;
    std::condition_variable _not_full;
};
