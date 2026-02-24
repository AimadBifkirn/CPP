#include "easyfind.hpp"

int main ()
{
    std::vector<int> vect;
    vect.push_back (1);
    vect.push_back (2);
    vect.push_back (3);
    vect.push_back (4);


    if (easyfind(vect, 3))
        std::cout << "Found !!" << std::endl;
    else
        std::cout << "Not found !!" << std::endl;
}
