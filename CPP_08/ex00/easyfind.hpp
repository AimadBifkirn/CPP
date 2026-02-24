#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
bool easyfind (const T& container, int toFind)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), toFind);
    return (it != container.end());
}