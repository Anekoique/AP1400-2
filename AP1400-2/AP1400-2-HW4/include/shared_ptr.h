#ifndef SHARED_PTR
#define SHARED_PTR

#include <stddef.h>

template <typename T>
class SharedPtr 
{
public:
    explicit SharedPtr(T* ptr = nullptr);
    ~SharedPtr();
    SharedPtr(SharedPtr<T>& ptr);
    size_t length();
    size_t use_count();
    T* get();
    void reset();
    void reset(T* ptr);
    T operator*();
    bool empty();
    SharedPtr<T>* operator->();
    SharedPtr<T>& operator=(const SharedPtr & other);
    SharedPtr<T>& operator=(SharedPtr&& other) noexcept;
    explicit operator bool();
private:
    T* _p;
    size_t* ref_count;
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : _p(ptr), ref_count(new size_t(1)) {}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& ptr) : _p(ptr._p), ref_count(ptr.ref_count)
{
    (*ref_count)++;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (_p == nullptr) return;
    if (*ref_count == 1)
    {
        delete _p;
        delete ref_count;
        _p = nullptr;
        ref_count = nullptr;
    }
    else if (*ref_count > 1)
    {
        (*ref_count)--;
    }
}

template <typename T>
T* SharedPtr<T>::get()
{
    return _p;
}

template <typename T>
T SharedPtr<T>::operator*()
{
    return *_p;
}

template <typename T>
SharedPtr<T>* SharedPtr<T>::operator->()
{
    return this;
}

template <typename T>
void SharedPtr<T>::reset()
{
    delete _p;
    _p = nullptr;
    (*ref_count) = 0;
}

template <typename T>
void SharedPtr<T>::reset(T* ptr)
{
    if (ptr != _p)
    {
        reset();
        _p = ptr;
        *ref_count = 1;
    }
}

template <typename T>
T* make_shared(T value)
{
    T* ptr = new T(value);
    return ptr;
}

template <typename T>
bool SharedPtr<T>::empty()
{
    return !_p;
}

template <typename T>
SharedPtr<T>::operator bool()
{
    return _p;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr & other)
{
    if (this != &other)
    {
        this->~SharedPtr();
        _p = other._p;
        ref_count = other.ref_count;
        (*ref_count)++;
    }
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr && other) noexcept
{
    if (this != &other)
    {
        this->~SharedPtr();
        _p = other._p;
        ref_count = other.ref_count;
        other._p = nullptr;
        other.ref_count = nullptr;
    }
    return *this;
}

template <typename T>
size_t SharedPtr<T>::use_count()
{
    return ref_count == nullptr ? 0 : *ref_count;
}
template <typename T>
size_t SharedPtr<T>::length()
{
    return (*_p).size();
}
#endif //SHARED_PTR
