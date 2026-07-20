#ifndef VECTOR_IMPL_H
#define VECTOR_IMPL_H

#include <iostream>
#include <stddef.h>  // for type: size_t
#include <stdexcept> // for std::out_of_range
#include "07-vector.h"

template <typename T>
Vector<T>::Vector() : size_(0), vals_(nullptr) {}

template <typename T>
Vector<T>::Vector(size_t n) : size_(n), vals_(new T[n]) {}

template <typename T>
Vector<T>::Vector(size_t n, T val) : size_(n), vals_(new T[n]) {
    for(size_t i = 0; i < size_; ++i)
        vals_[i] = val;
}

template <typename T>
Vector<T>::~Vector() {
    if(vals_ != nullptr)
        delete[] vals_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& obj)
{
    // Protect against self-assignment (x = x)
    if (this == &obj)
        return *this;

    // Allocate new memory first
    T* new_vals = new T[obj.size_];

    // Copy the values
    for (size_t i = 0; i < obj.size_; ++i)
        new_vals[i] = obj.vals_[i];

    // Delete old memory
    delete[] vals_;

    // Update members
    size_ = obj.size_;
    vals_ = new_vals;

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& obj) {
    size_ = obj.size_;
    if(vals_ != nullptr)
        delete[] vals_;
    vals_ = new T[size_];
    for(size_t i = 0; i < size_; ++i)
        vals_[i] = (obj.vals_)[i];    

    return *this;    
}

template <typename T>
T& Vector<T>::operator[](size_t i) {
    if(i >= size_)
        throw(std::out_of_range("Index out of range"));

    return vals_[i];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const {
    if(i >= size_)
        throw(std::out_of_range("Index out of range"));

    return vals_[i];
}
#endif
