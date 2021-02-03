
// 实际的shared_ptr<>实现，引用计数使用 atomic 原子变量来实现
template<typename T>
class SharedPtr {
public:
    SharedPtr(): _t(nullptr), _count(nullptr) {};
    SharedPtr(T* t): _t(t) {
        if (t != nullptr) {
            _count = new uint32(1);
        }
    }
    ~SharedPtr() {
        reset();
    };

    SharedPtr(const SharedPtr& p) {
        _t = p._t;
        _count = p._count;
        if (_count) {
            *_count ++;
        }
    }

    SharedPtr& operator= (const SharedPtr& p) {
        if (this == &p) {
            return *this;
        }
        this->_t = p._t;
        this->_count = p._count;
        if (this->_count)
            (*this->_count) ++;
        return *this;
    }

    T* operator -> () {
        return _t;
    }

    T* get() const {
        return _t;
    }

    int count() const {
        return _count ? *_count: 0;
    }

    void reset() {
        if (*_count) {
            *_count --;
            if (*_count == 0) {
                delete _t;
                delete _count;
            }
        }
    }
private:
    T* _t;
    uint32_t* _count;
};
