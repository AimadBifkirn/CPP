#include "easyfind.hpp"

int main ()
{
    int arr[4] = {1, 2, 3, 4};
    std::vector<int> vect(arr, arr + 4);

    try
    {
        std::cout << *easyfind(vect, 1) << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}
