#ifndef SHARED_PTR
#define SHARED_PTR

#include <stddef.h>

template <typename T>
class SharedPtr 
{
public:
    SharedPtr();
    SharedPtr(T* ptr);
    ~SharedPtr();
    SharedPtr(SharedPtr<T>& ptr);
    int use_count();
    size_t length();
    T* get();
    void reset();
    void reset(T* ptr);
    T operator*();
    bool check();
    bool empty();
    SharedPtr<T>* operator->();
    explicit operator bool();
private:
    T* _p;
    static int count;
};

template <typename T>
int SharedPtr<T>::count = 0;

template <typename T>
SharedPtr<T>::SharedPtr()
{
    _p = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)
{
    _p = ptr;
    count += 1;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& ptr)
{
    _p = ptr.get();
    count += 1;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (check() && count == 1)
    {
        delete _p;
        _p = nullptr;
        count--;
    }
    else if (check() && count >= 1)
        count--;
}

template <typename T>
int SharedPtr<T>::use_count()
{
    return count;
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
    _p = nullptr;
    count -= 1;
}

template <typename T>
void SharedPtr<T>::reset(T* ptr)
{
    _p = ptr;
}

template <typename T>
bool SharedPtr<T>::check()
{
    return _p == nullptr ? false : true;
}

template <typename T>
T* make_shared(T value)
{
    T* ptr = new T(value);
    return ptr;
}

template <typename T>
size_t SharedPtr<T>::length()
{
    return (*_p).size();
}

template <typename T>
bool SharedPtr<T>::empty()
{
    if (_p == nullptr)
        return true;
    else
        return false;
}

template <typename T>
SharedPtr<T>::operator bool()
{
    if (_p == nullptr) return false;
    else return true;
}
#endif //SHARED_PTR
