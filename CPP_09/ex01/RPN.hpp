#pragma once

#include <iostream>
#include <stack>
#include <sstream>

class RPN
{
    private:
        std::stack<int>  st;
    public:
        RPN ();
        RPN (const RPN &other);
        RPN &operator= (const RPN &obj);
        ~RPN ();


        void calculate (std::string expression);
};