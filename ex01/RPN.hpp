#pragma once
#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN& source);
		RPN&	operator=(const RPN& source);
		~RPN(void);

		void	Calc(const std::string& input);
};
#endif
