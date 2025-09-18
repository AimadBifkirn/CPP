#include "main.hpp"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Arguments number must be 3!!" << std::endl;
		return (1);
	}
	if ((std::string(argv[2])).empty() || (std::string(argv[3])).empty())
	{
		std::cerr << "Empty args are not exepted !" << std::endl;
		return (1);
	}
	std::ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		std::cerr << "Failed to open the file : " << argv[1] << std::endl;
		return (1); 
	}
	std::ofstream outputFile(((std::string)argv[1] + ".replace").c_str());
	if (!outputFile)
	{
		inputFile.close();
		std::cerr << "Failed to create the output file(.replace) !!" << std::endl;
		return (1);
	}
	std::string	line;
	while (std::getline(inputFile,line))
	{
		size_t	pos = 0;
		while ((pos = line.find(argv[2], pos)) != std::string::npos)
		{
			std::string	s1 = line.substr(0, pos);
			std::string	s2 = line.substr(pos + ((std::string)argv[2]).length(), line.length());
			line = s1 + (std::string)argv[3] + s2;
			pos += ((std::string)argv[3]).length();
		}
		outputFile << line << std::endl;
	}
	inputFile.close();
	outputFile.close();
	return (0);
}
