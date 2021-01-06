#include <stdint.h>
#include <atomic>
constexpr uint8_t WRITABLE = 0;
constexpr uint8_t WRITE_LOCKED = 0xFF;

class ScopedReadLock {
public:
    ScopedReadLock(std::atomic<uint8_t>& data) _data(data) {
        for (uint8_t val = _data.load(std::memory_order_consume);
            val == WRITE_LOCKED || !_data.compare_exchange_strong(val, val + 1, std::memory_order_release, std::memory_order_relaxed);
            val = _data.load(std::memory_order_consume));
    };
    ~ ScopedReadLock() {
        for (uint8_t val = _data.load(std::memory_order_consume);
            _data.compare_exchange_strong(val, val - 1, std::memory_order_release, std::memory_order_relaxed);
            val = _data.load(std::memory_order_consume));
    }
private:
    std::atomic<uint8_t>& _data;
};


class ScopedWriteLock {
public:
    ScopedWriteLock(std::atomic<uint8_t>& data) _data(data) {
        for (uint8_t val = _data.load(std::memory_order_consume);
            val != WRITABLE || _data.compare_exchange_strong(WRITABLE, WRITE_LOCKED, std::memory_order_release, std::memory_order_relaxed);
            val = _data.load(std::memory_order_consume));
    };
    ~ ScopedWriteLock() {
        assert(_data.compare_exchange_strong(WRITE_LOCKED, WRITABLE, std::memory_order_release, std::memory_order_relaxed));
    }
private:
    std::atomic<uint8_t>& _data;
};