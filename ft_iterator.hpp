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
};

#endif