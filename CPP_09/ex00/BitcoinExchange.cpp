#include "BitcoinExchange.hpp"

static void parseDate (const std::string &date)
{
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        throw std::runtime_error("invalid date: " + date);

    if (y < 0 || d < 1 || d > 31 || m < 1 || m > 12)
        throw std::runtime_error ("Error: bad input => " + date);
    // i might have to check for the months with 30 days and february
}

void BitcoinExchange::parse (const std::string &fileName)
{
    std::fstream file (fileName.c_str());
    if (!file.is_open ())
        throw std::runtime_error ("Error: could not open file");
    std::string line;
    int i = 0;
    while (std::getline (file, line))
    {
        if (i++ == 0)
        {
            if (line != "date,exchange_rate")
                throw std::runtime_error ("Error: invalid header");
            continue;
        }
        size_t pos = line.find (",");
        if (pos != std::string::npos)
        {
            std::string date = line.substr (0, pos);
            parseDate (date);
            std::stringstream ss (line.substr (pos + 1));
            double value;
            if (!(ss >> value) || !(ss >> std::ws).eof())
                throw std::runtime_error("Error: invalid value");
            DateValue[date] = value;
        }
        else
            throw std::runtime_error ("Error: invalid line format");
    }

    if (file.eof ())
        file.close ();
     else
        throw std::runtime_error ("Error: could not read file");

}

BitcoinExchange::BitcoinExchange ()
{
    parse ("data.csv");
}

BitcoinExchange::BitcoinExchange (const std::string &fileName)
{
    parse (fileName);
}

BitcoinExchange::BitcoinExchange (const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator= (const BitcoinExchange &obj)
{
    if (this != &obj)
        DateValue = obj.DateValue;
    return *this;
}

BitcoinExchange::~BitcoinExchange ()
{
}

static std::string trimWhiteSpaces (const std::string &str)
{
    size_t start = str.find_first_not_of (" \t");
    size_t end = str.find_last_not_of (" \t");
    if (start == std::string::npos || end == std::string::npos)
        return "";
    return str.substr (start, end - start + 1);
}

void BitcoinExchange::printall (const std::string &inputFile)
{
    std::fstream file (inputFile.c_str());
    if (!file.is_open ())
        throw std::runtime_error ("Error: could not open file");
    std::string line;
    int i = 0;
    while (std::getline (file, line))
    {

        line = trimWhiteSpaces (line);

        if (i++ == 0)
        {
            if (line != "date | value")
                throw std::runtime_error ("Error: invalid header");
            continue;
        }
        size_t pos = line.find ("|");
        if (pos != std::string::npos)
        {
            std::string date = line.substr (0, pos);
            parseDate (date);
            std::stringstream ss (line.substr (pos + 1));
            double value;
            if (!(ss >> value) || value < 0)
            {
                std::cout << "Error: not a positive number." << std::endl;
                continue;
            }
            if (value > 1000)
            {
                std::cout << "Error: too large a number." << std::endl;
                continue;
            }
            
            if (DateValue.find (date) != DateValue.end ())
                std::cout << date << " => " << value << " = " << value * DateValue[date] << std::endl;
            else
            {
                std::map<std::string, double>::iterator it = DateValue.lower_bound (date);
                if (it == DateValue.begin ())
                    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
                else
                {
                    --it;
                    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
                }
            }
        }
        else
            std::cout << "Error: bad input => " << line << std::endl;
    }

    if (file.eof ())
        file.close ();
     else
        throw std::runtime_error ("Error: could not read file");
}