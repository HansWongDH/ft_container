#include <iterator>
#include <vector>
#include <iostream>
#include <map>
#include "./includes/map.hpp"

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int	main(void)
{
	// ft::vector<int> x(5, 10);
	// ft::vector<int>::iterator it = x.begin();

	// std::cout << it.getPointer() << std::endl;

	ft::map<int, int> lol;

	ft::map<int, int> test;

	lol = test;
	// ft::map<int, int> test;
	// for (int i = 1; i < 10;i++)
	// 	lol.insert(ft::make_pair<const int, int>(i, i * 3));


	// ft::map<int,int>::const_iterator c_it = lol.begin();
	// for (; it != lol.end();it++)
	// 	ft::cout << lol.upper_bound(-10)->first << ft::endl;
	// lol.insert(ft::make_pair<int, int>(5, 4));
	// lol.insert(ft::make_pair<int, int>(3, 4));
	// lol.insert(ft::make_pair<int, int>(2, 4));
	// 	lol.insert(ft::make_pair<int, int>(1, 4));
	// lol.print();
	// lol.erase(++lol.begin());
	// lol.print();
	// printSize(lol);
	// it++;
	// it++;
	// it++;
	// ft::map<int, int> test(lol);
	// lol.clear();
	// std::map<int, int> lol2;
	// for (int i = 1; i < 10;i++)
	// 	lol2.insert(std::make_pair<const int, int>(i, i * 3));
	// std::map<int, int> test2;

	// test2 = lol2;
	// lol2.clear();
	// 	for (std::map<int, int>::iterator it = test2.begin(); it!= test2.end();it++)
	// 		std::cout << it->first << std::endl;
	// // lol.print();
	// for (std::map<int, int>::iterator test = lol.begin(); test != lol.end(); test++)
	// 	std::cout << test->first << std::endl;
	// lol.print();
	// ft::map<int, int>::iterator itb = lol.begin();
	// ft::map<int, int>::iterator ite = lol.end();

	// test.insert(itb, ite);
	// ft::map<int, int>::iterator ttb = test.begin();
	// ft::map<int, int>::iterator tte = test.end();
	// // itb;
	// // std::cout << itb->data.first << std::endl;
	// // itb.isNULL():
	// // // ft::pair<int, int> lol = ft::make_pair(3, 5);
	// // for (ft::map<int, int>::iterator it = ttb; it != tte; it++)
	// 	std::cout << lol.erase(3) << std::endl;

	// 	lol.print();
	// std::cout << lol.insert(ft::make_pair(4, 5)).first->data.first << std::endl;
	// test.insert(itb, ite);
	

}