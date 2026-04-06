#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <sstream>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void sortVector (const std::vector<int> &vect);
    void sortDeque (const std::deque<int> &deq);
};