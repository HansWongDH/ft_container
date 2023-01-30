#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include <iostream>

namespace	ft
{
	template <typename Type>
	class random_access_iterator{
	public:
        typedef Type       value_type;
    	typedef Type*  		pointer;
		typedef Type&		reference;
		typedef ptrdiff_t	difference_type;

		random_access_iterator();
		~random_access_iterator();
		random_access_iterator(pointer p);
		random_access_iterator(const random_access_iterator &a);
		random_access_iterator&	operator=(const random_access_iterator &a);

		random_access_iterator::reference	operator*(void);
		random_access_iterator&	operator++(void);
		random_access_iterator&	operator++(int);
		random_access_iterator&	operator--(void);
		random_access_iterator&	operator--(int);
		random_access_iterator	operator+(difference_type);
		random_access_iterator	operator-(difference_type);
		random_access_iterator::difference_type	operator-(random_access_iterator &a);
		bool	operator!=(const random_access_iterator &a);
		bool	operator==(const random_access_iterator &a);
		bool	operator>(const random_access_iterator &a);
		bool	operator<(const random_access_iterator &a);
		bool	operator>=(const random_access_iterator &a);
		bool	operator<=(const random_access_iterator &a);
		random_access_iterator&	operator+=(int);
		random_access_iterator&	operator-=(int);
		random_access_iterator::reference	operator[](int);
		
		private:
			pointer	_p;
	};

	template<bool, class T>    //i give it two parameters, up to you to give more or less
	struct enable_if
	{};

	template <class T>
	struct enable_if<true, T>
	{
    	typedef T type;     //if true define the T type value
	};

	template <class T, T v>
	struct integral_constant   //integral C++ struct in C++98 manner
	{
		typedef T value_type;
		typedef integral_constant<T,v> type;
		static const T value = v;
		operator T() { return value; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename T>
	struct is_integral : public false_type{};
	
	template<>
	struct is_integral<char> : public true_type{};
};

#endif