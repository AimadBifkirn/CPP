#pragma once 

#include <iostream>

template <typename T>
void swap (T &arg1, T &arg2)
{
    T temp = arg1;
    arg1 = arg2;
    arg2 = temp;
}

template <typename T>
T min (T num1, T num2)
{
    return (num1 >= num2 ? num2 : num1);
}

template <typename T>
T max (T num1, T num2)
{
    return (num1 <= num2 ? num2 : num1);
}