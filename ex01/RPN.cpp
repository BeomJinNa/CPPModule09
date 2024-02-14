#include <sstream>
#include <stack>
#include <iostream>
#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN& source)
{
	(void)source;
}

RPN&	RPN::operator=(const RPN& source)
{
	if (this != &source)
	{
	}

	return (*this);
}

RPN::~RPN(void)
{
}

void	RPN::Calc(const std::string& input)
{
	std::stack<double>	stack;
	std::istringstream	iss(input);

	std::string	buffer;
	double		former;
	double		latter;

	while (iss >> buffer)
	{
		if (buffer.size() > 1)
		{
			std::cerr << "Error (only 1 character available as a parameter)" << std::endl;
			return;
		}
		char	c = buffer[0];
		if (c != '+' && c != '-' && c != '*' && c != '/')
		{
			if (c < '0' || '9' < c)
			{
				std::cerr << "Error (unknown character)" << std::endl;
				return;
			}
			stack.push(c - '0');
			continue;
		}

		if (stack.empty())
		{
			std::cerr << "Error (invalid operation)" << std::endl;
			return;
		}
		latter = stack.top(); stack.pop();
		if (stack.empty())
		{
			std::cerr << "Error (invalid operation)" << std::endl;
			return;
		}
		if (c == '/' && latter == 0)
		{
		{
			std::cerr << "Error (division by 0)" << std::endl;
			return;
		}
		}
		former = stack.top(); stack.pop();

		switch (c)
		{
			case '+': stack.push(former + latter); break;
			case '-': stack.push(former - latter); break;
			case '*': stack.push(former * latter); break;
			case '/': stack.push(former / latter); break;
		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error (invalid operation)" << std::endl;
		return;
	}
	std::cout << stack.top() << std::endl;
}
