#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

class BitcoinExchange
{
    private:
        std::map<std::string, double> DateValue;
        void parse(const std::string &fileName);
    public:
        BitcoinExchange ();
        BitcoinExchange (const std::string &fileName);
        BitcoinExchange (const BitcoinExchange &other);
        BitcoinExchange &operator= (const BitcoinExchange &obj);
        ~BitcoinExchange ();

        void printall(const std::string &inputFile);

};