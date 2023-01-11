
#include "ft_iterator.hpp"

template<typename Type>
ft::random_access_iterator<Type>::random_access_iterator(void) : _p (NULL)
{
	// std::cout << "default random_access_iterator constructed" << std::endl;
}

template<typename Type>
ft::random_access_iterator<Type>::~random_access_iterator()
{
	// std::cout << "random_access_iterator destructed" << std::endl;
}

template<typename Type>
ft::random_access_iterator<Type>::random_access_iterator(pointer p) : _p(p)
{
	// std::cout << "random_access_iterator constructed" << std::endl;
}

template<typename Type>
ft::random_access_iterator<Type>::random_access_iterator(const ft::random_access_iterator<Type> &a)
{
	if (a._p != NULL)
		this->_p = a._p;
	// std::cout << "random_access_iterator copy constructor called" << std::endl;
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator=(const ft::random_access_iterator<Type> &a)
{
	if (a._p != NULL)
	{
		this->_p = a._p;
		std::cout << "random_access_iterator copy assignment called" << std::endl;
	}
	return (*this);

}

template<typename Type>
bool	ft::random_access_iterator<Type>::operator==(const ft::random_access_iterator<Type> &a)
{
	return (this->_p == a._p);
}

template<typename Type>
bool	ft::random_access_iterator<Type>::operator!=(const ft::random_access_iterator<Type> &a)
{
	return (this->_p != a._p);
}
template<typename Type>
typename ft::random_access_iterator<Type>::reference	ft::random_access_iterator<Type>::operator*(void)
{
	return (*(this->_p));
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator++(void)
{
	++this->_p;
	return (*this);
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator++(int)
{
	this->_p++;
	return (*this);
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator--(void)
{
	--this->_p;
	return (*this);
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator--(int)
{
	this->_p++;
	return (*this);
}

template<typename Type>
ft::random_access_iterator<Type>	ft::random_access_iterator<Type>::operator+(difference_type n)
{
	return this->_p + n;
}

template<typename Type>
ft::random_access_iterator<Type>	operator+(typename ft::random_access_iterator<Type>::difference_type n, ft::random_access_iterator<Type> &a)
{
	return (a + n);
}
template<typename Type>
ft::random_access_iterator<Type>	ft::random_access_iterator<Type>::operator-(difference_type n)
{
	return random_access_iterator(this->_p - n);
}

template<typename Type>
typename ft::random_access_iterator<Type>::difference_type	ft::random_access_iterator<Type>::operator-(ft::random_access_iterator<Type> &a)
{
	return (this->_p - a._p);
}

template<typename Type>
bool	ft::random_access_iterator<Type>::operator>(const ft::random_access_iterator<Type> &a)
{
	return (this->_p > a._p);
}

template<typename Type>
bool	ft::random_access_iterator<Type>::operator>=(const ft::random_access_iterator<Type> &a)
{
	return (this->_p >= a._p);
}
template<typename Type>
bool	ft::random_access_iterator<Type>::operator<(const ft::random_access_iterator<Type> &a)
{
	return (this->_p < a._p);
}
template<typename Type>
bool	ft::random_access_iterator<Type>::operator<=(const ft::random_access_iterator<Type> &a)
{
	return (this->_p <= a._p);
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator+=(int n)
{
	this->_p += n;
	return (*this);
}

template<typename Type>
ft::random_access_iterator<Type>&	ft::random_access_iterator<Type>::operator-=(int n)
{
	this->_p -= n;
	return (*this);
}

template<typename Type>
typename ft::random_access_iterator<Type>::reference	ft::random_access_iterator<Type>::operator[](int n)
{
	return (*(this->_p + n));
}