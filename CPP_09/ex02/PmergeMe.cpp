#include "PmergeMe.hpp"

PmergeMe::PmergeMe ()
{
    this->hasLeftOver = false;
}

PmergeMe::PmergeMe (const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator= (const PmergeMe &obj)
{
    this->hasLeftOver = obj.hasLeftOver;
    return *this;
}

PmergeMe::~PmergeMe ()
{
}

void PmergeMe::makePairs (const std::vector<int> &vect, std::vector<int> &bigs, std::vector<int> &smalls)
{
    for (size_t i = 0; i < vect.size(); i++)
    {
        int pair[2];
        pair[0] = vect[i];
        if (i + 1 < vect.size())
        {
            pair[1] = vect[i + 1];
            i++;
        }
        else
        {
            this->hasLeftOver = true;
            return ;
        }
        if (pair[0] < pair[1])
        {
            smalls.push_back(pair[0]);
            bigs.push_back(pair[1]);
        }
        else
        {
            smalls.push_back(pair[1]);
            bigs.push_back(pair[0]);
        }
    }
}

void PmergeMe::sortVector (const std::vector<int> &vect)
{
    std::vector<int> bigs;
    std::vector<int> smalls;
    makePairs (vect, bigs, smalls);
    if (vect.size() <= 1)
        return ;
    sortVector (bigs);
    // jacobhstal insertion logic :)
}