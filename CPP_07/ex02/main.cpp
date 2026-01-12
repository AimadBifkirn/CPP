#include "Array.hpp"

int main ( void )
{
    Array<int> arr(5);

    for (unsigned int i = 0; i < arr.size(); i++) {
        arr[i] = i * 10;
    }

    for (unsigned int i = 0; i < arr.size(); i++) {
        std::cout << "Element at index " << i << ": " << arr[i] << std::endl;
    }

    try {
        std::cout << arr[10] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}