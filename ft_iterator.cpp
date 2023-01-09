#include "ft_iterator.hpp"
#include <iostream>

ft::iterator::iterator(void)
{
	std::cout << "Iterator constructed" << std::endl;
}

ft::iterator::~iterator(void)
{
	std::cout << "Iterator destructed" << std::endl;
}

ft::iterator::iterator(const ft::iterator &a)
{
	std::cout << "Iterator copy constructor called" << std::endl;
}

ft::iterator&	ft::iterator::operator=(const ft::iterator &a)
{
	std::cout << "Iterator copy assignment called" << std::endl;
}

ft::iterator&	ft::iterator::operator==(const ft::iterator &a)
{
}