#include "RPN.hpp"

RPN::RPN ()
{
}

RPN::RPN (const RPN &other)
{
    *this = other;
}

RPN &RPN::operator= (const RPN &obj)
{
    this->st = obj.st;
    return *this;
}

RPN::~RPN ()
{
}

void RPN::calculate (std::string expression)
{
    std::stringstream ss (expression);
    std::string token;
    while (ss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (st.size () < 2)
                throw std::runtime_error ("Error: invalid expression");
            int b = st.top ();
            st.pop ();
            int a = st.top ();
            st.pop ();
            if (token == "+")
                st.push (a + b);
            else if (token == "-")
                st.push (a - b);
            else if (token == "*")
                st.push (a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error ("Error: division by zero");
                st.push (a / b);
            }
        }
        else
        {
            std::stringstream convert (token);
            int num;
            if(!(convert >> num) || !(convert >> std::ws).eof() || num > 9)
                throw std::runtime_error ("Error: invalid token");
            st.push (num);
        }
    }
    if (st.size () != 1)
        throw std::runtime_error ("Error: invalid expression");
    std::cout << st.top () << std::endl;
}