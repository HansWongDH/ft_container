#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template<
    class T,
    class Container = ft::vector<T>
> class stack{
	
	protected:
		Container	c;
	public:
	typedef Container	container_type;
	typedef typename container_type::value_type	value_type;
	typedef	typename container_type::size_type	size_type;
	typedef	typename container_type::reference reference;
	typedef	typename container_type::const_reference const_reference;

	explicit stack( const Container& cont = Container()) : c(cont)
	{

	}
	~stack() 
	{

	};

	stack( const stack& other )
	{
		*this = other;
	}

	stack	&operator=(const stack& other)
	{
		if (*this != other)
			*this = other;
		return *this;
	}	

	reference top(void)
	{
		return c.back();
	}
	const_reference top (void) const
	{
		return c.back();
	}

	bool empty(void) const
	{
		return c.empty();
	}

	size_type size(void) const
	{
		return c.size();
	}

	void push( const value_type& value )
	{
		c.push_back(value);
	}
	void pop(void)
	{
		c.pop_back();
	}

	Container	getC(void) const
	{
		return c;
	}

};

template< class T, class Container >
bool operator==( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
				{
					return lhs.getC() == rhs.getC();
				}

template< class T, class Container >
bool operator!=( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
				 {
					return lhs.getC() != rhs.getC();
				 }

template< class T, class Container >
bool operator< ( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
				 {
					return lhs.getC() < rhs.getC();
				 }

template< class T, class Container >
bool operator<=( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
				 {
					return lhs.getC() <= rhs.getC();
				 }

template< class T, class Container >
bool operator> ( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
				 {
					return lhs.getC() > rhs.getC();
				 }

template< class T, class Container >
bool operator>=( const ft::stack<T, Container>& lhs,
                 const ft::stack<T, Container>& rhs )
				 {
					return lhs.getC() >= rhs.getC();
				 }

} // namespace ft


#endif
