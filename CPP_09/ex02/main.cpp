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
        if (!(iss >> num) || num < 0)
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        vect.push_back(num);
    }
    std::cout << "Before: ";
    for (size_t i = 0; i < vect.size(); i++)
    {
        std::cout << vect[i] << " ";
        if ((i == 4 && vect.size() > 5))
        {
            std::cout << "[...] ";
            break;
        }
    }
    std::cout << std::endl;
    PmergeMe pmergeMe;
    clock_t start_V = clock();
    pmergeMe.sortVector(vect);
    clock_t end_V = clock();
    std::cout << "After: ";
    for (size_t i = 0; i < vect.size(); i++)
    {
        std::cout << vect[i] << " ";
        if ((i == 4 && vect.size() > 5))
        {
            std::cout << "[...] ";
            break;
        }
    }        
    std::cout << std::endl;
    std::deque<int> deq(vect.begin(), vect.end());
    // for (int i = 1; i < argc; i++)
    // {
    //     std::istringstream iss(argv[i]);
    //     int num;
    //     if (!(iss >> num))
    //     {
    //         std::cerr << "Error: Invalid number '" << argv[i] << "'" << std::endl;
    //         return 1;
    //     }
    //     deq.push_back(num);
    // }
    clock_t start_D = clock();
    pmergeMe.sortDeque(deq);
    clock_t end_D = clock();
    // for (size_t i = 0; i < deq.size(); i++)
    //     std::cout << deq[i] << " ";
    // std::cout << std::endl;
    std::cout << "Time to process a range of  " << vect.size() << " elements with std::vector : " << (double)(end_V - start_V) / CLOCKS_PER_SEC * 1000 << " us" << std::endl;
    std::cout << "Time to process a range of  " << deq.size() << " elements with std::deque : " << (double)(end_D - start_D) / CLOCKS_PER_SEC * 1000 << " us" << std::endl;
    return 0;
}