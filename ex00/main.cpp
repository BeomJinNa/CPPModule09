#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int	main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return (1);
	}

	std::string	inputFileName = argv[1];

	BitcoinExchange exchange;
	if (!exchange.GetData("data.csv"))
	{
		std::cerr << "Error: Failed to read data file." << std::endl;
		return (1);
	}

	std::ifstream	ifs(inputFileName);
	std::string		line;
	while (std::getline(ifs, line))
	{
		exchange.Convert(line);
	}
	if (!ifs.eof())
	{
		std::cerr << "Error: Failed to read input file." << std::endl;
	}

	return (0);
}
