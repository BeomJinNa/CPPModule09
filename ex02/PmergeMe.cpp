#include <iostream>
#include <iomanip>
#include <cassert>
#include "PmergeMe.hpp"

namespace
{
	void				arrangeSubchain(const Vector& main, Vector& sub);
	void				arrangeSubchain(const List& main, List& sub);
	void				insertElements(Vector& main, const Vector& sub);
	void				insertElements(List& main, const List& sub);
	std::vector<int>	getSequenceListToInsert(std::size_t size);
	void				insertBinarySearch(Vector& main, const Pair& element,
										   std::size_t size);
	void				insertBinarySearch(List& main, const Pair& element,
										   std::size_t size);
#ifdef LOG_ON
	void				printMainSubSet(const Vector& main, const Vector& sub);
#endif
}

PmergeMe::PmergeMe(void) {}
PmergeMe::PmergeMe(const PmergeMe& source) { (void)source; }
PmergeMe&	PmergeMe::operator=(const PmergeMe& source) { if (this != &source) {} return (*this); }
PmergeMe::~PmergeMe(void) {}

void	PmergeMe::SortVector(Vector& vector)
{
	if (vector.size() < 2)
	{
#ifdef LOG_ON
		std::cout << "\033[32m---------------start insertion---------------\033[0m" << std::endl;
#endif
		return ;
	}

	MakePair(vector);
	Vector	mainChain(vector.begin(), vector.begin() + vector.size() / 2);
	Vector	subChain(vector.begin() + vector.size() / 2, vector.end());
	std::vector<int>	tempIndex = SaveIndex(mainChain);

	assert(mainChain.size() <= subChain.size());

#ifdef LOG_ON
	printMainSubSet(mainChain, subChain);
	std::cout << std::endl;
#endif

	ReWriteIndex(mainChain);
	SortVector(mainChain);

	arrangeSubchain(mainChain, subChain);
	LoadIndex(mainChain, tempIndex);

#ifdef LOG_ON
	std::cout << std::endl;
	printMainSubSet(mainChain, subChain);
#endif

	insertElements(mainChain, subChain);
	vector = mainChain;
}

void	PmergeMe::SortList(List& list)
{
	if (list.size() < 2)
	{
		return ;
	}

	MakePair(list);

	List			mainChain;
	List			subChain;
	List::iterator	it = list.begin();
	for (std::size_t i = 0; i < list.size() / 2; ++i)
	{
		mainChain.push_back(*it++);
	}
	for (std::size_t i = list.size() / 2; i < list.size(); ++i)
	{
		subChain.push_back(*it++);
	}

	std::vector<int>	tempIndex = SaveIndex(mainChain);

	assert(mainChain.size() <= subChain.size());

	ReWriteIndex(mainChain);
	SortList(mainChain);

	arrangeSubchain(mainChain, subChain);
	LoadIndex(mainChain, tempIndex);

	insertElements(mainChain, subChain);
	list = mainChain;
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

List	PmergeMe::MakeList(const std::vector<int>& vector)
{
	List	output;

	for (std::size_t i = 0; i < vector.size(); ++i)
	{
		output.push_back(std::make_pair<int, int>(vector[i], i));
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

void	PmergeMe::ReWriteIndex(List& list)
{
	int i = 0;
	for (List::iterator it = list.begin(); it != list.end(); ++it)
	{
		(*it).second = i++;
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

std::vector<int>	PmergeMe::SaveIndex(const List& mainChain)
{
	std::vector<int>	output;

	List::const_iterator		it = mainChain.begin();
	for (std::size_t i = 0; i < mainChain.size(); ++i)
	{
		output.push_back((*it).second);
		++it;
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

void	PmergeMe::LoadIndex(List& mainChain, const std::vector<int>& indexVector)
{
	assert(mainChain.size() == indexVector.size());
	for (List::iterator it = mainChain.begin(); it != mainChain.end(); ++it)
	{
		(*it).second = indexVector[(*it).second];
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

void	PmergeMe::MakePair(List& list)
{
	std::size_t	size = list.size();

	List::iterator	formerIt = list.begin();
	List::iterator	latterIt = list.begin();
	std::advance(latterIt, size / 2);

	for (std::size_t i = 0; i < size / 2; ++i)
	{
		if ((*formerIt).first < (*latterIt).first)
		{
			Pair	temp = *formerIt;
			*formerIt = *latterIt;
			*latterIt = temp;
		}
		++formerIt;
		++latterIt;
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

void	PmergeMe::PrintList(const List& list)
{
	if (list.empty())
	{
		return ;
	}

	List::const_iterator it = list.begin();
	for (std::size_t i = 0; i < list.size() - 1; ++i)
	{
		std::cout << std::setw(DIGIT) << (*it).first << " ";
		++it;
	}
	std::cout << std::setw(DIGIT) << (*it).first;
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

	void	arrangeSubchain(const List& main, List& sub)
	{
		const List	temp(sub);
		Pair		lastElem = std::make_pair<int, int>(0, -1);

		if (main.size() < sub.size())
		{
			lastElem = sub.back();
		}

		sub.clear();

		for (List::const_iterator it = main.begin(); it != main.end(); ++it)
		{
			List::const_iterator	subIt = temp.begin();

			std::advance(subIt, (*it).second);
			sub.push_back(*subIt);
		}

		if (lastElem.second != -1)
		{
			sub.push_back(lastElem);
		}
	}

	void	insertElements(Vector& main, const Vector& sub)
	{
		const std::vector<int>	sequence = getSequenceListToInsert(sub.size());
#ifdef LOG_ON
		std::cout << "\033[36m     ";
		PmergeMe::PrintVector(sequence);
		std::cout << "\n" << std::endl;
#endif

		for (std::size_t i = 0; i < sub.size(); ++i)
		{
			insertBinarySearch(main, sub[sequence[i]], sequence[i] + i + 1);
#ifdef LOG_ON
			std::cout << "     ";
			PmergeMe::PrintVectorHighlight(main, sub[sequence[i]].first);
#endif
		}
	}

	void	insertElements(List& main, const List& sub)
	{
		const std::vector<int>	sequence = getSequenceListToInsert(sub.size());

		for (std::size_t i = 0; i < sub.size(); ++i)
		{
			List::const_iterator	subIt = sub.begin();
			std::advance(subIt, sequence[i]);
			insertBinarySearch(main, *subIt, sequence[i] + i + 1);
		}
	}

	std::vector<int>	getSequenceListToInsert(std::size_t size)
	{
		std::vector<int>	output(size);
		std::size_t			pow = 1;
		std::size_t			index;

		for (std::size_t i = 0; i < size; ++i)
		{
			if (i + 1 >= pow)
			{
				pow *= 2;
				index = pow - 2; // index + 1 = pow - 1
				if (index >= size)
				{
					index = size - 1;
				}
			}
			output[i] = index--;
		}
		return (output);
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

	void	insertBinarySearch(List& main, const Pair& element, std::size_t size)
	{
		if (size > main.size())
		{
			size = main.size();
		}

		std::size_t	begin = 0;
		std::size_t	end = size;
		std::size_t	mid = (begin + end) / 2;

		List::iterator	itBegin = main.begin();
		List::iterator	itEnd = main.end();
		List::iterator	itMid = main.begin();
		std::advance(itMid, (begin + end) / 2);

		while (begin != end)
		{
			if ((*itMid).first < element.first)
			{
				begin = mid + 1;
				std::advance(itBegin, mid - begin + 1);
				mid = (begin + end) / 2;
				itMid = itBegin;
				std::advance(itMid, (begin + end) / 2);
			}
			else
			{
				end = mid;
				itEnd = itMid;
				mid = (begin + end) / 2;
				itMid = itBegin;
				std::advance(itMid, (begin + end) / 2);
			}
		}
		main.insert(itMid, element);
	}

#ifdef LOG_ON
	void	printMainSubSet(const Vector& main, const Vector& sub)
	{
		std::cout << "\033[33mmain ";
		PmergeMe::PrintVector(main);
		std::cout << "\033[0m" << std::endl;
		std::cout << "sub  ";
		PmergeMe::PrintVector(sub);
		std::cout << std::endl;
	}
#endif
}

#ifdef LOG_ON
void	PmergeMe::PrintVectorHighlight(const Vector& vector, int filter)
{
	if (vector.size() == 0)
	{
		return ;
	}

	for (std::size_t i = 0; i < vector.size() - 1; ++i)
	{
		if (vector[i].first == filter)
			std::cout << "\033[33m";
		std::cout << std::setw(DIGIT) << vector[i].first << " ";
		if (vector[i].first == filter)
			std::cout << "\033[0m";
	}
	if (vector[vector.size() - 1].first == filter)
		std::cout << "\033[33m";
	std::cout << std::setw(DIGIT) << vector[vector.size() - 1].first;
	if (vector[vector.size() - 1].first == filter)
		std::cout << "\033[0m";
	std::cout << std::endl;
}
#endif