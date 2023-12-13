#include "PmergeMe.hpp"

template <typename T>
T inserSort(T vect)
{
	T vec(vect);
	for (size_t i = 1; i < vec.size(); ++i)
	{
		int pos = vec[i];
		int j = i - 1;

		while (j >= 0 && vec[j] >= pos)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j +1 ] = pos;
	}
	return vec;
}

template <typename T>
T merge(T first, T sec)
{
	T merged;
	
	typename T::iterator fit = first.begin();
	typename T::iterator sit = sec.begin();
	while (fit != first.end() && sit != sec.end())
	{
		if (*fit <= *sit)
			merged.push_back(*fit++);
		else
			merged.push_back(*sit++);
	}
	if (fit != first.end() )
		merged.insert(merged.end(), fit, first.end());
	else
		merged.insert(merged.end(), sit, sec.end());

	return merged;
}

template <typename T>
T mergeVec(T vec )
{
	if (vec.size() <= 4)
		return inserSort(vec);
	T first(vec.begin(), vec.begin()+(vec.size()/2) );
	T sec(vec.begin()+(vec.size()/2) , vec.end() );
	first = mergeVec(first);
	sec = mergeVec(sec);
	return merge(first, sec);
}

int main(int ac, char **av)
{
	clock_t v_start;
	clock_t d_start;
	clock_t v_end;
	clock_t d_end;
	if (ac < 3)
	{
		std::cout << "Error: bad arguments!" << std::endl;
		return (1);
	}
	std::vector<int> vec;
	std::deque<int> dq;
	fillContainer(vec, dq, ac, av);
	std::cout << "Before:  " ;
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << " " << vec[i];
	std::cout << std::endl;
	v_start = clock();
	vec = mergeVec(vec);
	v_end = clock();
	std::cout << "After :  " ;
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << " " << vec[i];
	std::cout << std::endl;
	d_start = clock();
	dq = mergeVec(dq);
	d_end = clock();
	std::cout << "Time to process a range of " << vec.size() << " elements by std::vector is : "<< (v_end - v_start) << " us" << std::endl;
	std::cout << "Time to process a range of " << dq.size() << " elements by std::deque  is : " << (d_end - d_start)<< " us" << std::endl;
}
