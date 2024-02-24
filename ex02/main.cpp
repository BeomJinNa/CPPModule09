#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <vector>
#include "PmergeMe.hpp"

namespace
{
	void					getInput(std::vector<int>& input, int argc, char* argv[]);
	std::pair<Vector, List> sortInput(std::vector<int>& input);
	void					writeResultIntoFile(const Vector& vector, const List& list);
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <input values, ...>" << std::endl;
		return (0);
	}

	std::vector<int>	input(argc - 1);
	getInput(input, argc, argv);

	std::pair<Vector, List>	result = sortInput(input);

	writeResultIntoFile(result.first, result.second);

	return (0);
}

namespace
{
	void	getInput(std::vector<int>& input, int argc, char* argv[])
	{
		for (int i = 0; i < argc - 1; ++i)
		{
			std::istringstream	iss(argv[i + 1]);
			iss >> input[i];
			if (iss.fail() || input[i] < 0)
			{
				std::cerr << "Error: invalid input" << std::endl;
				exit(1);
			}
		}
	}

	std::pair<Vector, List> sortInput(std::vector<int>& input)
	{
		timeval	vectorStart;
		timeval	vectorEnd;
		timeval	listStart;
		timeval	listEnd;

		std::cout << "Before: ";
		PmergeMe::PrintVector(input);
		std::cout << std::endl;

#ifdef LOG_ON
		std::cout << "\033[32m====================Sorting====================\033[0m" << std::endl;
#endif

		gettimeofday(&vectorStart, NULL);
		Vector	vector = PmergeMe::WrapVector(input);
		PmergeMe::SortVector(vector);
		gettimeofday(&vectorEnd, NULL);

#ifdef LOG_ON
		std::cout << "\033[32m====================SortEnd====================\033[0m" << std::endl;
#endif

		std::cout << "After:  ";
		PmergeMe::PrintVector(vector);
		std::cout << std::endl;

		gettimeofday(&listStart, NULL);
		List	list = PmergeMe::MakeList(input);
		PmergeMe::SortList(list);
		gettimeofday(&listEnd, NULL);

#ifndef LOG_ON
		double	timeVector = (vectorEnd.tv_sec - vectorStart.tv_sec) * 1e6
			+ (vectorEnd.tv_usec - vectorStart.tv_usec);
		double	timeList = (listEnd.tv_sec - listStart.tv_sec) * 1e6
			+ (listEnd.tv_usec - listStart.tv_usec);

		std::cout << "Time to process a range of " << std::setw(DIGIT) << input.size()
			<< " elements with std::vector : " << timeVector << " us" << std::endl;
		std::cout << "Time to process a range of " << std::setw(DIGIT) << input.size()
			<< " elements with std::list   : " << timeList << " us" << std::endl;
#endif

		return (std::make_pair(vector, list));
	}

	void	writeResultIntoFile(const Vector& vector, const List& list)
	{
		std::ofstream	ossVector("output_vector.txt");
		std::ofstream	ossList("output_list.txt");

		if (ossVector.is_open())
		{
			for (std::size_t i = 0; i < vector.size(); ++i)
			{
				ossVector << vector[i].first << std::endl;
			}
		}
		if (ossList.is_open())
		{
			List::const_iterator	it = list.begin();
			for (std::size_t i= 0; i < list.size(); ++i)
			{
				ossList << (*it).first << std::endl;
				++it;
			}
		}
	}
}
