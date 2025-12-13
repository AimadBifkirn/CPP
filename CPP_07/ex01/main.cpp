#include "iter.hpp"

char function(int& v) {
    v *= 10;
    return 42;
}

int main ()
{

    int arr[3] = {1, 2, 3};

    iter(arr, 3, function);

    std::cout << arr[0] << std::endl;
    std::cout << arr[1] << std::endl;
    std::cout << arr[2] << std::endl;

    return (0);
}