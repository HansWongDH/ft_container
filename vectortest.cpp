#include "ft_vector.hpp"
#include <iostream>

int	main(void)
{
	ft::vector<int>	haha(3, 10);


	ft::vector<int> lol;

	lol.assign(haha.begin(), haha.end());
	// ft::Vector<int>::iterator it = lol.ft_iterator();

	// for (int i = 0; i < 5; i++)
	// 	std::cout << *(it + 4) << std::endl;
	for (ft::vector<int>::iterator it = lol.begin(); it != lol.end(); it++)
		std::cout << *it << std::endl;

	
}