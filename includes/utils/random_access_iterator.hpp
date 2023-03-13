
#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iostream>
#include <limits>
# include <cstddef>
#include <ostream>
#include <typeinfo>
# include <sstream>

#include "utilities.hpp"


namespace	ft
{
	template <typename T>
	class random_access_iterator {
	public:
        typedef typename Iterator<std::random_access_iterator_tag, T>::value_type	    	value_type;
    	typedef typename Iterator<std::random_access_iterator_tag, T>::pointer 			pointer;
		typedef typename Iterator<std::random_access_iterator_tag, T>::reference			reference;
		typedef typename Iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
		typedef typename Iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

		random_access_iterator() : _p (nullptr_t) {

		}
		~random_access_iterator() {

		}
		random_access_iterator(pointer p) : _p(p) {

		}

		random_access_iterator(const random_access_iterator &a) : _p(a._p){

			// std::cout << "random_access_iterator copy constructor called" << std::endl;
		}
		random_access_iterator&	operator=(const random_access_iterator &a) {
			if (a._p != NULL)
			{
				this->_p = a._p;
				// std::cout << "random_access_iterator copy assignment called" << std::endl;
			}
			return (*this);
		}

		reference	operator*(void) const {
			return (*(this->_p));
		}

		pointer	getPointer(void) const
		{
			return (this->_p);
		}
		pointer	operator->(void) {
			return (&(this->operator*()));
		}
		random_access_iterator &operator++(void) {
			_p++;
			return (*this);
		}
		random_access_iterator	operator++(int) {
			random_access_iterator tmp (*this);
			++this->_p;
			return (tmp);
		}
		random_access_iterator	&operator--(void) {
			_p--;
			return (*this);
		}
		random_access_iterator	operator--(int) {
			random_access_iterator tmp (*this);
			--this->_p;
			return (tmp);
		}
		random_access_iterator	operator+(difference_type n) const {
			return this->_p + n;
		}
		random_access_iterator	operator-(difference_type n)  const {
			return this->_p - n;
		}
		difference_type	operator-(random_access_iterator &a) const {
			return (this->_p - a._p);
		}
		// bool	operator!=(const random_access_iterator &a) {
		// 	return (this->_p != a._p);
		// }
		// bool	operator==(const random_access_iterator &a) {
		// 	return (this->_p == a._p);
		// }
		// bool	operator>(const random_access_iterator &a) {
		// 	return (this->_p > a._p);
		// }
		// bool	operator<(const random_access_iterator &a) {
		// 	return (this->_p < a._p);
		// }
		// bool	operator>=(const random_access_iterator &a) {
		// 	return (this->_p >= a._p);
		// }
		// bool	operator<=(const random_access_iterator &a) {
		// 	return (this->_p <= a._p);
		// }
		random_access_iterator&	operator+=(int n) {
			this->_p += n;
			return (*this);
		}
		random_access_iterator&	operator-=(int n) {
			this->_p -= n;
			return (*this);
		}
		reference	operator[](int n) {
			return (*(this->_p + n));
		}
		
		operator random_access_iterator<const T> (void) const{
			return random_access_iterator<const T>(this->_p);
		}
		private:
			pointer	_p;
	};

	template< typename L, typename R >
	bool operator==( const ft::random_access_iterator<L>& lhs,
					const ft::random_access_iterator<R>& rhs ) {
			return lhs.getPointer()  == rhs.getPointer() ;
		};

	template< typename L, typename R >
	bool operator!=( const ft::random_access_iterator<L>& lhs,
					const ft::random_access_iterator<R>& rhs ) {
			return lhs.getPointer()  != rhs.getPointer() ;
		};


	template< typename L, typename R >
	bool operator<( const ft::random_access_iterator<L>& lhs,
					const ft::random_access_iterator<R>& rhs ) {
			return lhs.getPointer()  < rhs.getPointer() ;
		};


	template< typename L, typename R >
	bool operator<=( const ft::random_access_iterator<L>& lhs,
					const ft::random_access_iterator<R>& rhs ) {
			return lhs.getPointer()  <= rhs.getPointer() ;
		};

	template< typename L, typename R >
	bool operator>( const ft::random_access_iterator<L>& lhs,
					const ft::random_access_iterator<R>& rhs ) {
			return lhs.getPointer()  > rhs.getPointer() ;
		};

	template< typename L, typename R >
	bool operator>=( const ft::random_access_iterator<L>& lhs,
					const ft::random_access_iterator<R>& rhs ) {
			return lhs.getPointer()  >=	 rhs.getPointer() ;
		};


	template< typename T>
	bool operator==( const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs ) {
			return lhs.getPointer()  == rhs.getPointer() ;
		};

	template< typename T>
	bool operator!=( const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs ) {
			return lhs.getPointer()  != rhs.getPointer() ;
		};


	template< typename T>
	bool operator<( const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs ) {
			return lhs.getPointer()  < rhs.getPointer() ;
		};


	template< typename T>
	bool operator<=( const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs ) {
			return lhs.getPointer()  <= rhs.getPointer() ;
		};

	template< typename T>
	bool operator>( const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs ) {
			return lhs.getPointer()  > rhs.getPointer() ;
		};

	template< typename T>
	bool operator>=( const ft::random_access_iterator<T>& lhs,
					const ft::random_access_iterator<T>& rhs ) {
			return lhs.getPointer()  >=	 rhs.getPointer() ;
		};

	template< typename T>
	typename ft::random_access_iterator<T>::difference_type
	operator-(ft::random_access_iterator<T>& lhs, ft::random_access_iterator<T>& rhs ) 
	{
			return lhs.getPointer() - rhs.getPointer() ;
		};

	template< typename L, typename R>
	typename ft::random_access_iterator<L>::difference_type	operator-(const ft::random_access_iterator<L>& lhs,  const ft::random_access_iterator<R>& rhs ) 
	{
			return lhs.getPointer() - rhs.getPointer() ;
		};

	template< typename T>
	ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n,  ft::random_access_iterator<T> &it ) 
	{
			return it + n;
	};

};



template<typename Type>
std::ostream&	operator<< (std::ostream &os, ft::random_access_iterator<Type> &a) {
	return os << a;
}

// namespace	ft
// {
// 	template <typename Type>
// 	class random_access_iterator{
// 	public:
//         typedef Type       value_type;
//     	typedef Type*  		pointer;
// 		typedef Type&		reference;
// 		typedef ptrdiff_t	difference_type;

// 		random_access_iterator();
// 		~random_access_iterator();
// 		random_access_iterator(pointer p);
// 		random_access_iterator(const random_access_iterator &a);
// 		random_access_iterator&	operator=(const random_access_iterator &a);

// 		random_access_iterator::reference	operator*(void);
// 		random_access_iterator&	operator++(void);
// 		random_access_iterator&	operator++(int);
// 		random_access_iterator&	operator--(void);
// 		random_access_iterator&	operator--(int);
// 		random_access_iterator	operator+(difference_type);
// 		random_access_iterator	operator-(difference_type);
// 		random_access_iterator::difference_type	operator-(random_access_iterator &a);
// 		bool	operator!=(const random_access_iterator &a);
// 		bool	operator==(const random_access_iterator &a);
// 		bool	operator>(const random_access_iterator &a);
// 		bool	operator<(const random_access_iterator &a);
// 		bool	operator>=(const random_access_iterator &a);
// 		bool	operator<=(const random_access_iterator &a);
// 		random_access_iterator&	operator+=(int);
// 		random_access_iterator&	operator-=(int);
// 		random_access_iterator::reference	operator[](int);
		
// 		private:
// 			pointer	_p;
// 	};

// 	template<bool, class T>    //i give it two parameters, up to you to give more or less
// 	struct enable_if
// 	{};

// 	template <class T>
// 	struct enable_if<true, T>
// 	{
// 		typedef T type;     //if true define the T type value
// 	};

// 	template<class T>
// 	struct is_integral{
// 		public:
// 			static const bool value = std::numeric_limits<T>::is_integer;
// 	};



// };


#endif


