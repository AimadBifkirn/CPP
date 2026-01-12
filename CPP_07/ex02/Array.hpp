#pragma once

#include <iostream>

template <typename T>
class Array {
private:
    T* elements;
    unsigned int size;
public:
    Array();
    Array(unsigned int n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    unsigned int getSize() const;
};