#include <iostream>
#include "RPN.hpp"

int	main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
		return (1);
	}

	RPN	rpn;

	rpn.Calc(argv[1]);

	return (0);
}
