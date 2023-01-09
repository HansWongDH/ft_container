#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>

template <class T,class Allocator = std::allocator<T> >
class Vector
{
	private:
		T*		_data;
		size_t	size;
	public:
		typedef T			value_type;
		typedef Allocator	allocator_type;
		typedef size_t		size_type;
		typedef	Allocator::reference	reference;
		typedef	Allocator::const_reference	const_reference;
		typedef T*							pointer;
		typedef	retarded_iterator			iterator;
		typedef retarded_const_iterator		const_iterator;
		typedef retarded_reverse_iterator	reverse_iterator;
		typedef	const_retarded_reverse_iterator	const_reverse_iterator;

		Vector();
		~Vector();
		~Vector(int n, int val);
		Vector(const Vector &a);
		Vector&	operator=(const Vector&a);

};
#endif