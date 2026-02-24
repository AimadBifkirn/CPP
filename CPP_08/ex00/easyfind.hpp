#pragma once

#include <iostream>
#include <vector>

template <typename T>
bool easyfind (const T& container, int toFind)
{
    typename T::iterator it = container.begin();
    while (it != container.end())
    {
        if (*it == toFind)
            return true;
        it++;
    }
    return false;
}