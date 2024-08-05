#include <iostream>
#include <iomanip>
#include <cassert>
#include <utility>
#include "PmergeMe.hpp"

namespace
{
	void				arrangeSubchain(const Vector& main, Vector& sub);
	void				insertElements(Vector& main, const Vector& sub);
	void				insertBinarySearch(Vector& main, const Pair& element,
										   std::size_t size);

	std::vector<int>	getSequenceListToInsert(std::size_t size);
}

void	PmergeMe::SortVector(Vector& vector)
{
	if (vector.size() < 2)
	{
		return ;
	}

	MakePair(vector);
	Vector	mainChain(vector.begin(), vector.begin() + vector.size() / 2);
	Vector	subChain(vector.begin() + vector.size() / 2, vector.end());
	std::vector<int>	tempIndex = SaveIndex(mainChain);

	assert(mainChain.size() <= subChain.size());


	ReWriteIndex(mainChain);
	SortVector(mainChain);

	arrangeSubchain(mainChain, subChain);
	LoadIndex(mainChain, tempIndex);


	insertElements(mainChain, subChain);
	vector = mainChain;
}

Vector	PmergeMe::WrapVector(const std::vector<int>& vector)
{
	Vector	output(vector.size());

	for (std::size_t i = 0; i < vector.size(); ++i)
	{
		output[i].first = vector[i];
		output[i].second = i;
	}

	return (output);
}

void	PmergeMe::ReWriteIndex(Vector& vector)
{
	for (std::size_t i = 0; i < vector.size(); ++i)
	{
		vector[i].second = i;
	}
}

std::vector<int>	PmergeMe::SaveIndex(const Vector& mainChain)
{
	std::vector<int>	output(mainChain.size());

	for (std::size_t i = 0; i < mainChain.size(); ++i)
	{
		output[i] = mainChain[i].second;
	}
	return (output);
}

void	PmergeMe::LoadIndex(Vector& mainChain, const std::vector<int>& indexVector)
{
	assert(mainChain.size() == indexVector.size());
	for (std::size_t i = 0; i < mainChain.size(); ++i)
	{
		mainChain[i].second = indexVector[mainChain[i].second];
	}
}

void	PmergeMe::MakePair(Vector& vector)
{
	std::size_t	size = vector.size();
	std::size_t	j = size / 2;
	for (std::size_t i = 0; i < size / 2; ++i)
	{
		if (vector[i].first < vector[j].first)
		{
			Pair	temp = vector[i];
			vector[i] = vector[j];
			vector[j] = temp;
		}
		++j;
	}
}

void	PmergeMe::PrintVector(const std::vector<int>& vector)
{
	if (vector.empty())
	{
		return ;
	}

	for (std::size_t i = 0; i < vector.size() - 1; ++i)
	{
		std::cout << std::setw(DIGIT) << vector[i] << " ";
	}
	std::cout << std::setw(DIGIT) << vector[vector.size() - 1];
}

void	PmergeMe::PrintVector(const Vector& vector)
{
	if (vector.empty())
	{
		return ;
	}

	for (std::size_t i = 0; i < vector.size() - 1; ++i)
	{
		std::cout << std::setw(DIGIT) << vector[i].first << " ";
	}
	std::cout << std::setw(DIGIT) << vector[vector.size() - 1].first;
}

namespace
{
	void	arrangeSubchain(const Vector& main, Vector& sub)
	{
		const Vector	temp(sub);

		for (std::size_t i = 0; i < main.size(); ++i)
		{
			sub[i] = temp[main[i].second];
		}
	}

	void	insertElements(Vector& main, const Vector& sub)
	{
		const std::vector<int>	sequence = getSequenceListToInsert(sub.size());

		for (std::size_t i = 0; i < sub.size(); ++i)
		{
			insertBinarySearch(main, sub[sequence[i]], sequence[i] + i + 1);
		}
	}

	void	insertBinarySearch(Vector& main, const Pair& element, std::size_t size)
	{
		if (size > main.size())
		{
			size = main.size();
		}

		std::size_t	begin = 0;
		std::size_t	end = size;
		std::size_t	mid = (begin + end) / 2;

		while (begin != end)
		{
			if (main[mid].first < element.first)
			{
				begin = mid + 1;
				mid = (begin + end) / 2;
			}
			else
			{
				end = mid;
				mid = (begin + end) / 2;
			}
		}

		main.insert(main.begin() + mid, element);
	}

	std::vector<int>	getSequenceListToInsert(std::size_t size)
	{
		std::vector<int>	output(size);
		std::size_t			pow = 2;
		std::size_t			lastStart = 1;
		std::size_t			index = 0;

		for (std::size_t i = 0; i < size; ++i)
		{
			if (i + 1 > lastStart)
			{
				pow *= 2;
				lastStart = pow - lastStart; // (index + 1) + lastStart = pow
				index = lastStart - 1;
				if (index >= size)
				{
					index = size - 1;
				}
			}
			output[i] = index--;
		}
		return (output);
	}

}

PmergeMe::PmergeMe(void) {}
PmergeMe::PmergeMe(const PmergeMe& source) { (void)source; }
PmergeMe&	PmergeMe::operator=(const PmergeMe& source) { if (this != &source) {} return (*this); }
PmergeMe::~PmergeMe(void) {}
