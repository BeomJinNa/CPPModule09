#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "BitcoinExchange.hpp"

namespace
{
	int		GetKeyFromDate(const std::string& date);
	bool	IsValidDate(int year, int month, int day);
	int		GetDaysInMonth(int year, int month);
	bool	IsLeapYear(int year);
}

bool	BitcoinExchange::GetData(const std::string& fileName)
{
	std::ifstream	ifs(fileName);

	if (ifs.fail())
	{
		std::cerr << "Error: Unable to open file " << fileName
				  << " for reading" << std::endl;
		return (false);
	}
	std::string	line;
	while (std::getline(ifs, line))
	{
		ParseLine(line);
	}
	if (!ifs.eof())
	{
		std::cerr << "Error: Problem occurred while reading the file." << std::endl;
		return (false);
	}
	return (true);
}

void	BitcoinExchange::ParseLine(std::string& line)
{
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

	std::size_t			delimiter = line.find(',');
	if (delimiter == std::string::npos || delimiter + 1 >= line.length())
	{
		return ;
	}

	std::string date = line.substr(0, delimiter);
	line = line.substr(delimiter + 1);

	std::istringstream	iss(line);

	double	value;
	iss >> value;
	if (!iss)
	{
		return ;
	}

	int key = GetKeyFromDate(date);

	if (key >= 0)
	{
		mData[(key)] = value;
	}
}

void	BitcoinExchange::Convert(const std::string& line) const
{
	std::istringstream	ifs(line);
	std::string			date;
	int					dateConverted;
	int					iValue;
	double				value;
	char				delim;

	ifs >> date >> delim >> iValue;
	if (delim != '|' || !ifs)
	{
		return ;
	}
	dateConverted = GetKeyFromDate(date);
	if (dateConverted < 0)
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return ;
	}

	if (iValue < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return ;
	}
	else if (iValue > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return ;
	}

	DB::const_iterator	it = mData.upper_bound(dateConverted);

	if (it == mData.begin())
	{
		std::cerr << "Error: can not find reference data from the csv file" << std::endl;
		return ;
	}
	--it;

	value = iValue * it->second;


	std::cout << std::fixed;
	std::cout << date << " => " << iValue << " = "
		<< std::setprecision(2) << value << std::endl;
}

namespace
{
	int	GetKeyFromDate(const std::string& date)
	{
		std::istringstream	iss(date);
		int					year;
		int 				month;
		int 				day;
		char				delim1;
		char				delim2;

		iss >> year >> delim1 >> month >> delim2 >> day;

		if (iss
		 && delim1 == '-'
		 && delim2 == '-'
		 && IsValidDate(year, month, day))
		{
			return ((year * 10000) + (month * 100) + day);
		}
		return (-1);
	}

	bool IsValidDate(int year, int month, int day)
	{
		return (year >= 0
			 && month >= 1
			 && month <= 12
			 && day >= 1
			 && day <= GetDaysInMonth(year, month));
	}

	int GetDaysInMonth(int year, int month)
	{
		static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (month == 2 && IsLeapYear(year))
		{
			return (29);
		}
		if (month < 1 || month > 12)
		{
			return (-1);
		}
		return days[month - 1];
	}

	bool IsLeapYear(int year)
	{
		return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
	}
}

BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& source) : mData(source.mData) {}
BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& source)
{ if (this != &source) { mData = source.mData; } return (*this); }
BitcoinExchange::~BitcoinExchange(void) {}
