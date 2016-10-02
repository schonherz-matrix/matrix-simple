#pragma once

#include <memory>
#include <algorithm>
#include <iostream>

template <typename T>
class Array2D {
public: 
    Array2D (void);
    Array2D (size_t sx, size_t sy);
    Array2D (const Array2D&) = default;
    virtual ~Array2D ();

    Array2D<T>& operator= (const Array2D&) = default;
    size_t getWidth () const;
    size_t getHeight () const;

    T& operator() (size_t x, size_t y);
    const T& operator() (size_t x, size_t y) const;

    Array2D<T> deep () const;
    Array2D<T> shallow ();
    const Array2D<T> shallow () const;
    void toDeep () const;

    void resize (size_t nx, size_t ny);
    
    bool isShallow () const;
    bool isNull () const;
private:
    size_t width;
    size_t height;
    std::shared_ptr<T> store;
};

template <typename T>
inline Array2D<T>::Array2D (void)
    : width(0), height(0), store ( nullptr )
{
}

template <typename T> 
inline Array2D<T>::Array2D (size_t x, size_t y)
    : width(x), height(y), store (new T[x*y])
{
}

template <typename T> 
inline Array2D<T>::~Array2D () 
{
}

template <typename T> 
inline size_t Array2D<T>::getWidth () const 
{
    return width;
}


template <typename T> 
inline size_t Array2D<T>::getHeight () const 
{
    return height;
}

template <typename T>
inline T& Array2D<T>::operator() (size_t x, size_t y)
{
   return reinterpret_cast<T*>(store.get()) [y * width + x];
}

template <typename T>
inline const T& Array2D<T>::operator() (size_t x, size_t y) const
{
   return reinterpret_cast<T*>(store.get()) [y * width + x];
}

template <typename T> 
inline Array2D<T> Array2D<T>::deep() const 
{
    Array2D<T> copy = Array2D<T> (width, height);
    std::copy (store.get(), store.get() + width*height * sizeof(T), copy.store.get());
    return copy;
}

template <typename T>
inline Array2D<T> Array2D<T>::shallow ()
{    
    Array2D<T> copy;
    copy.width  = width; 
    copy.height = height;
    copy.store  = store; // The magic here is std::shared_ptr<T> operator= ()

    return std::move(copy); 
}

template <typename T> 
inline const Array2D<T> Array2D<T>::shallow() const 
{
    Array2D<T> copy;
    copy.width  = width;
    copy.height = height;
    copy.store  = store; // The magic here is std::shared_ptr<T> operator= ()

    return std::move(copy);
}

template <typename T>
inline void Array2D<T>::toDeep() const
{
    if (!isShallow ()) 
        return;

    std::shared_ptr<T> newstore (new T[width*height]);
    std::copy (store.get (), store.get () + width*height * sizeof(T), newstore.get ());
    const_cast< std::shared_ptr<T>& >(store). swap (newstore);
}

template <typename T>
inline void Array2D<T>::resize (size_t nx, size_t ny) 
{
    store.reset (new T[nx*ny]);
    width = nx; height = ny;
} 

template <typename T>
inline bool Array2D<T>::isNull () const
{
    return store.get == nullptr;
}

template <typename T>
inline bool Array2D<T>::isShallow() const
{
    return isNull() || store.use_count () > 1;
}

template <typename T>
std::ostream& operator<< (std::ostream& stream, Array2D<T> array);
