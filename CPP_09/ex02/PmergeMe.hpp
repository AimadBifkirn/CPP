#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <sstream>

class PmergeMe
{
    private:
        bool hasLeftOver;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void sortVector (const std::vector<int> &vect);
        void sortDeque (const std::deque<int> &deq);
        void makePairs (const std::vector<int> &vect, std::vector<int> &bigs, std::vector<int> &smalls);
};