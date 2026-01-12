#pragma once
#include <iostream>

template <typename T>
class Array {
    private:
        T* elements;
        unsigned int _size;
    public:
        Array() : elements(NULL), _size(0) {}

        Array(unsigned int n) {
            _size = n;
            elements = new T[n]();
        }

        Array(const Array& other)
        {
            if (other._size == 0)
            {
                this->elements = NULL;
                this->_size = 0;
                return;
            }
            this->elements = new T[other._size]();
            this->_size = other._size;
            for (unsigned int i = 0; i < other._size; i++) {
                this->elements[i] = other.elements[i];
            }
        }

        Array& operator=(const Array& other)
        {
            if (this == &other)
                return *this;
            delete[] this->elements;
            if (other._size == 0)
            {
                this->elements = NULL;
                this->_size = 0;
                return *this;
            }
            this->elements = new T[other._size]();
            this->_size = other._size;
            for (unsigned int i = 0; i < other._size; i++) {
                this->elements[i] = other.elements[i];
            }
            return *this;
        }

        ~Array() { delete[] elements; }

        T& operator[](unsigned int index)
        {
            if (index >= _size)
                throw std::out_of_range("Index out of bounds");
            return elements[index];
        }

        unsigned int size() const { return _size; }
};