#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Span
{
    private:
        unsigned int N;
        std::vector<int> vec;
    public:
        Span ();
        Span (unsigned int N);
        Span (const Span &other);
        Span& operator= (const Span &obj);

        ~Span ();

        void addNumber (int num);
        int shortestSpan();
        int longestSpan();
        void rangAdd (std::vector<int>::iterator begin, std::vector<int>::iterator end);
};