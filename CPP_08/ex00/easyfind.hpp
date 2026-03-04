#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
typename T::const_iterator easyfind (const T& container, int toFind)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), toFind);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}