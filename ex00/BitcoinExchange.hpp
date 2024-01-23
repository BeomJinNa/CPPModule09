#pragma once
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
	public:
		typedef std::map<int, double>	DB;

		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& source);
		BitcoinExchange&	operator=(const BitcoinExchange& source);
		~BitcoinExchange(void);

		bool	GetData(const std::string& fileName);
		void	Convert(const std::string& line) const;

	private:
		void	ParseLine(std::string& line);

		std::map<int, double>	mData;
};
#endif
