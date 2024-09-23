#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <stddef.h>

template <typename T>
class UniquePtr 
{
public:
    UniquePtr();
    UniquePtr(T* ptr);
    UniquePtr(UniquePtr<T>*& ptr)=delete;
    void reset();
    size_t length();
    bool check();
    bool empty();
    void reset(T* ptr);
    T* release();
    T operator*();
    UniquePtr<T>* operator->();
    explicit operator bool();
    T* get();
    ~UniquePtr();
private:
    T* _p;
    bool deleted;
};

template <typename T>
UniquePtr<T>::UniquePtr()
{
    _p = nullptr;
}

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr)
{
    _p = ptr;
}

template <typename T>
UniquePtr<T>::~UniquePtr()
{
    if (check())
    {
        delete _p;
        _p = nullptr;
    }
}

template <typename T>
T* UniquePtr<T>::get()
{
    return _p;
}

template <typename T>
T UniquePtr<T>::operator*()
{
    return *_p;
}

template <typename T>
void UniquePtr<T>::reset()
{
    _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* ptr)
{
    _p = ptr;
}

template <typename T>
UniquePtr<T>* UniquePtr<T>::operator->()
{
    return this;
}

template <typename T>
size_t UniquePtr<T>::length()
{
    return (*_p).size(); 
}

template <typename T>
T* make_unique(T value)
{
    T* ptr = new T(value);
    return ptr;
}

template <typename T>
bool UniquePtr<T>::check()
{
    return _p == nullptr ? false : true;
}

template <typename T>
T* UniquePtr<T>::release()
{
    T* ptr = new T(*_p);
    delete _p;
    _p = nullptr;
    return ptr;
}

template <typename T>
bool UniquePtr<T>::empty()
{
    if (_p == nullptr)
        return true;
    else
        return false;
}

template <typename T>
UniquePtr<T>::operator bool()
{
    if (_p == nullptr) return false;
    else return true;
}
#endif //UNIQUE_PTR
