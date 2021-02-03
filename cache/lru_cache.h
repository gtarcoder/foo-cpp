#include <unordered_map>
#include <list>
#include <shared_ptr>

template<typename K, typename V>
class LRUCache {
public:
    LRUCache(int capacity): _capacity(capacity) {};
    ~LRUCache() {};

private:
    std::unordered_map<K, std::shared_ptr<V>> _map;
    std::list<std::pair<>>
};

