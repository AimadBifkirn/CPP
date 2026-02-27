#include "Span.hpp"


Span::Span() : N(0)
{
}

Span::Span (unsigned int N) : N (N)
{
}

Span::Span (const Span &other) : N (other.N), vec (other.vec)
{
}

Span &Span::operator= (const Span& obj)
{
    this->N = obj.N;
    this->vec = obj.vec; // this->vec.assign(obj.vec.begin(), obj.vec.end())
    return *this;
}

Span::~Span()
{
}

void Span::addNumber (int num)
{
    if (vec.size() >= N)
        throw std::out_of_range("Span is full !!");
    vec.push_back(num);
}

int Span::longestSpan ()
{
    if (this->vec.size() <= 1)
        throw std::runtime_error ("Size must be bigger then 1 !!");
    std::sort (this->vec.begin(), this->vec.end());
    return vec[vec.size() - 1] - vec[0];
}

int Span::shortestSpan ()
{
    if (this->vec.size() <= 1)
        throw std::runtime_error ("Size must be bigger then 1 !!");
    std::sort (this->vec.begin(), this->vec.end());
    int result = std::numeric_limits<int>::max();
    for (size_t i = 0; i < this->vec.size() - 1; i++)
    {
        if ((this->vec[i + 1] - this->vec[i]) < result)
            result = this->vec[i + 1] - this->vec[i];
    }
    return result;
}

void Span::rangAdd (std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    if (std::distance(begin, end) + this->vec.size() > this->N)
        throw std::out_of_range("Span is full !!");
    this->vec.insert(this->vec.end(), begin, end);
}
