#pragma once
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <list>

# define DIGIT 2

typedef	std::pair<int, int>	Pair;
typedef std::vector<Pair>	Vector;
typedef std::list<Pair>		List;

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& source);
		PmergeMe&	operator=(const PmergeMe& source);
		~PmergeMe(void);

		static void				SortVector(Vector& vector);
		static void				SortList(List& list);
		static Vector			WrapVector(const std::vector<int>& vector);
		static List				MakeList(const std::vector<int>& vector);
		static void				ReWriteIndex(Vector& vector);
		static void				ReWriteIndex(List& list);
		static std::vector<int>	SaveIndex(const Vector& mainChain);
		static std::vector<int>	SaveIndex(const List& mainChain);
		static void				LoadIndex(Vector& mainChain,
										  const std::vector<int>& indexVector);
		static void				LoadIndex(List& mainChain,
										  const std::vector<int>& indexVector);
		static void				MakePair(Vector& vector);
		static void				MakePair(List& list);
		static void				PrintVector(const std::vector<int>& vector);
		static void				PrintVector(const Vector& vector);
		static void				PrintList(const List& list);

#ifdef LOG_ON
		static void				PrintVectorHighlight(const Vector& vector, int filter);
#endif
};
#endif
