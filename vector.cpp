#include "./includes/vector.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::string;


typedef ft::vector<int>::iterator ft_iterator;
	typedef std::vector<int>::iterator std_iterator;

	TEST_CASE("Default constructor") {
	ft::vector<int> ft;
	std::vector<int> std;
	
	REQUIRE(ft.size() == std.size());

	SUBCASE ("Assign") {
		ft.assign(3, 5);
		std.assign(3, 5);
		
		ft_iterator ft_it = ft.begin();
		std_iterator std_it = std.begin();

		CHECK(ft.size() == std.size());
		CHECK(*ft_it == *std_it);
		CHECK(*(ft_it + 2) == *(std_it + 2));
		ft::vector<int> ft_x;
		std::vector<int> std_x;
		ft_x.assign(ft.begin(), ft.end());
		std_x.assign(std.begin(), std.end());
		CHECK(ft_x.size() == std_x.size());
		ft_iterator it = ft_x.begin();
		std_iterator it2 = std_x.begin();
		while (it2 != std_x.end())
		{
			CHECK(*it == *it2);
			it++;
			it2++;
		};
		SUBCASE("Clear") {
		ft.clear();
		std.clear();
		CHECK(ft.empty() == std.empty());
		// CHECK(*ft_it == *std_it);
	}
	SUBCASE("erase") {
		for (int i = 0; i < 10; i++)
		{
			ft.push_back(i);
			std.push_back(i);
		}

		ft_iterator ft_erase = ft.begin();
		std_iterator std_erase = std.begin();

		// CHECK(*(ft.erase(ft.end()- 1)) == *(std.erase(std.end() - 1)));
		CHECK(*(ft.erase(ft_erase + 3, ft_erase + 5)) == *(std.erase(std_erase + 3, std_erase + 5)));
		CHECK(ft.size() == std.size());

		ft_erase = ft.begin();
		 std_erase = std.begin();
				std.clear();
		while (std_erase != std.end())
		{
			CHECK(*ft_erase == *std_erase);
			ft_erase++;
			std_erase++;
		};
	}
	SUBCASE("insert") {
		std.insert(std.begin() + 1, 20);
		ft.insert(ft.begin() + 1, 20);

		CHECK(ft.size() == std.size());
		CHECK(ft.capacity() == std.capacity());
		// CHECK(*std.end() == *ft.end());
		ft_iterator ft_insert = ft.begin();
		std_iterator std_insert = std.begin();
		while (std_insert != std.end())
		{
			CHECK(*ft_insert == *std_insert);
			// std::cout << *std_insert << std::endl;
			ft_insert++;
			std_insert++;
			
		};
		std.reserve(7);
		ft.reserve(7);
		// std:cout << "cap is " << ft.capacity() << std::endl;
		std.insert(std.begin() + 1, 5, 8);
		ft.insert(ft.begin() + 1, 5, 8);

		CHECK(ft.size() == std.size());
		CHECK(ft.capacity() == std.capacity());
		// std::cout << "cap is " << ft.capacity() << std::endl;
		ft_insert = ft.begin();
		std_insert = std.begin();
		while (ft_insert != ft.end())
		{
			CHECK(*ft_insert == *std_insert);
			// std::cout << *std_insert << std::endl;
			ft_insert++;
			std_insert++;
			
		};

		std::vector<int> std_test(5, 99);
		ft::vector<int>  ft_test(5, 99);
		
		std_iterator std_in_it = std_test.begin();
		ft_iterator ft_in_it = ft_test.begin();

		std.insert(std.begin() + 1, std_in_it, std_in_it + 4);
		ft.insert(ft.begin() + 1, ft_in_it, ft_in_it + 4);

		CHECK(ft.size() == std.size());
		CHECK(ft.capacity() == std.capacity());
		// std::cout << "cap is " << ft.capacity() << std::endl;
		ft_insert = ft.begin();
		std_insert = std.begin();
		while (ft_insert != ft.end())
		{
			CHECK(*ft_insert == *std_insert);
			// std::cout << *std_insert << std::endl;
			ft_insert++;
			std_insert++;
			
		};
		
		SUBCASE("iterator")
		{
			ft::vector<int> c_ft ( 5, 4);
			// ft::vector<const int> c_ft;

			// c_ft.assign(5, 10);
			// c_ft.assign(5, 10);

			// c_ft.begin();
			const ft::vector<int>::iterator test = c_ft.end();
			test - c_ft.begin();
			// c_std.begin();
		}

		SUBCASE("Pushback")
		{
			ft::vector<int> p_ft(8);
			std::vector<int> p_std(8);

			ft::vector<int>::const_iterator ite = p_ft.end();
			ft::vector<int>::iterator it = p_ft.begin();

			
			for (int i = 1; it != ite; ++i)
			{
				// cout << i << endl;
				*it++ = i;
			}

			
			// for (int i = 1; i < 5; i++)
			// {
			// 	p_ft.push_back(i * 3);
			// 	p_std.push_back(i * 3);
			// }

			// CHECK(p_ft.size() == p_std.size());
			// CHECK(p_ft.capacity() == p_std.capacity());
			// std_iterator it2 = p_std.begin();
			// for (ft_iterator it = p_ft.begin(); it != p_ft.end(); it++)
			// 	std::cout <<"ft :"<< *it << "std :" <<*it2 << endl;
		}

		SUBCASE("resize")
		{
			ft::vector<int> rz_ft(8);
			ft::vector<int> rz_std(8);

			rz_std.resize(10);

			// CHECK(rz_ft.size() == rz_std.size());
			CHECK(rz_ft != rz_std);
			// cout << "true or false : " <<ft::equal(rz_ft.begin(), rz_ft.end(), rz_std.begin()) << endl;
		}
	}
}
	}
