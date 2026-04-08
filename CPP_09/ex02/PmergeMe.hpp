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

        void sortVector (std::vector<int> &vect);
        void makePairs (const std::vector<int> &vect, std::vector<int> &bigs, std::vector<int> &smalls, int &leftover);

        void sortDeque (std::deque<int> &deq);
        void makePairs (const std::deque<int> &deq, std::deque<int> &bigs, std::deque<int> &smalls, int &leftover);
    };