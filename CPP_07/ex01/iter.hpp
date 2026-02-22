#pragma once

#include <iostream>


template <typename T, typename G>
void iter (T* address, const unsigned int lenght, G function)
{
    for (unsigned int i = 0; i < lenght; i++)
        function (address[i]);
}