#include <atomic>
#include <mutex>

class RWLock {
public:
    RWLock() {};
    ~RWLock() {};
    void lock_read() {
        std::unique_lock<std::mutex> guard(_mtx);

    };
    void lock_write() {

    };
    void unlock_read() {

    };
    void unlock_write() {

    };
private:
};