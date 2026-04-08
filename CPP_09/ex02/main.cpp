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
        if (!(iss >> num))
        {
            std::cerr << "Error: Invalid number '" << argv[i] << "'" << std::endl;
            return 1;
        }
        vect.push_back(num);
    }
    PmergeMe pmergeMe;
    pmergeMe.sortVector(vect);
    for (size_t i = 0; i < vect.size(); i++)
        std::cout << vect[i] << " ";
    std::cout << std::endl;
    return 0;
}