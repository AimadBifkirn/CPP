#include "PmergeMe.hpp"

PmergeMe::PmergeMe ()
{
}

PmergeMe::PmergeMe (const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator= (const PmergeMe &obj)
{
    (void)obj;
    return *this;
}

PmergeMe::~PmergeMe ()
{
}

void PmergeMe::makePairs (const std::vector<int> &vect, std::vector<int> &bigs, std::vector<int> &smalls, int &leftover)
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
            leftover = pair[0];
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

void PmergeMe::sortVector (std::vector<int> &vect)
{
    if (vect.size() <= 1)
        return ;
    std::vector<int> bigs;
    std::vector<int> smalls;
    int leftover = -1;
    makePairs (vect, bigs, smalls, leftover);
    sortVector (bigs);
    // jacobhstal insertion logic :)
    int first = 0;
    int second = 1;
    std::vector<int> insertOrder;
    while (second <= (int)smalls.size())
    {
        if (first == 0 && second == 1)
        {
            insertOrder.push_back(0);
            first = 1;
            second = 1;
        }
        else
        {
            int next = second + (2 * first);
            first = second;
            second = next;
        }
        for (int j = second - 1; j >= first; j--)
        {
            if (j < (int)smalls.size())
                insertOrder.push_back(j);
        }
    }

    for (size_t i = 0; i < insertOrder.size(); i++)
    {
        std::vector<int>::iterator it = std::lower_bound(bigs.begin(), bigs.end(), smalls[insertOrder[i]]);
        bigs.insert(it, smalls[insertOrder[i]]);
    }

    if (leftover != -1)
    {
        std::vector<int>::iterator it = std::lower_bound(bigs.begin(), bigs.end(), leftover);
        bigs.insert(it, leftover);
    }
    vect = bigs;
}




void PmergeMe::makePairs (const std::deque<int> &deq, std::deque<int> &bigs, std::deque<int> &smalls, int &leftover)
{
    for (size_t i = 0; i < deq.size(); i++)
    {
        int pair[2];
        pair[0] = deq[i];
        if (i + 1 < deq.size())
        {
            pair[1] = deq[i + 1];
            i++;
        }
        else
        {
            leftover = pair[0];
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

void PmergeMe::sortDeque (std::deque<int> &deq)
{
    std::deque<int> bigs;
    std::deque<int> smalls;
    int leftover = -1;
    makePairs (deq, bigs, smalls, leftover);
    if (deq.size() <= 1)
        return ;
    sortDeque (bigs);
    // jacobhstal insertion logic :)
    int first = 0;
    int second = 1;
    std::deque<int> insertOrder;
    for (size_t i = 0; i < smalls.size(); i++)
    {
        if (first == 0 && second == 1)
        {
            insertOrder.push_back(0);
            first = 1;
            second = 1;
        }
        else
        {
            int next = second + (2 * first);
            first = second;
            second = next;
        }
        for (int j = second - 1; j >= first; j--)
        {
            if (j < (int)smalls.size())
                insertOrder.push_back(j);
        }
    }

    for (size_t i = 0; i < insertOrder.size(); i++)
    {
        std::deque<int>::iterator it = std::lower_bound(bigs.begin(), bigs.end(), smalls[insertOrder[i]]);
        bigs.insert(it, smalls[insertOrder[i]]);
    }

    if (leftover != -1)
    {
        std::deque<int>::iterator it = std::lower_bound(bigs.begin(), bigs.end(), leftover);
        bigs.insert(it, leftover);
    }
    deq = bigs;
}