#include "PmergeMe.hpp"


int main (int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <numbers...>" << std::endl;
        return 1;
    }

    std::vector<int> vect;
    for (int i = 1; i < argc; i++)
    {
        std::istringstream iss(argv[i]);
        int num;
        if (!(iss >> num) || !(iss >> std::ws).eof() || num < 0)
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        vect.push_back(num);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < vect.size(); i++)
        std::cout << vect[i] << " ";
    std::cout << std::endl;

    PmergeMe pmergeMe;
    clock_t start_V = clock();
    pmergeMe.sortVector(vect);
    clock_t end_V = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < vect.size(); i++)
        std::cout << vect[i] << " ";    
    std::cout << std::endl;

    std::deque<int> deq(vect.begin(), vect.end());
    clock_t start_D = clock();
    pmergeMe.sortDeque(deq);
    clock_t end_D = clock();

    std::cout << "Time to process a range of  " << vect.size() << " elements with std::vector : " << static_cast<double>(end_V - start_V) * 1000000 / CLOCKS_PER_SEC << " us" << std::endl;
    std::cout << "Time to process a range of  " << deq.size() << " elements with std::deque : " << static_cast<double>(end_D - start_D) * 1000000 / CLOCKS_PER_SEC << " us" << std::endl;
    return 0;
}