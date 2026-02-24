#include "easyfind.hpp"

int main ()
{
    int arr[4] = {1, 2, 3, 4};
    std::vector<int> vect(arr, arr + 4);


    if (easyfind(vect, 3))
        std::cout << "Found !!" << std::endl;
    else
        std::cout << "Not found !!" << std::endl;
}
