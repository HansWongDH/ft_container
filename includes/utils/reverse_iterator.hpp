#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utilities.hpp"

namespace ft {

template<class Iterator>
class reverse_iterator {

	public:
	
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		/**
		 * @brief default constructor
		 * 
		 */
		reverse_iterator() : _it() {

		};

		/**
		 * @brief Construct a new initalizedreverse iterator object
		 * 
		 * @param x iterator
		 */
		explicit reverse_iterator( iterator_type x ) : _it(x) {

		};

		
		template
		<class U>
		reverse_iterator( const reverse_iterator<U>& other ) : _it(other.base()) {
			
		};
		template< class U >
		reverse_iterator	&operator=(const reverse_iterator<U>& other) {
			this->_it = other.base();
			return *this;
		};

		iterator_type	base() const {
			return _it;
		};

		/**
		 * @brief return reference
		 * 
		 * @return reference 
		 */
		reference operator*(void) const {
			iterator_type tmp = _it;
			return *(--tmp);
		}

		pointer operator->(void) const {
			return &(operator*());
		}

		// /**
		//  * @brief it doesn't have destructor because it a wrapper for existing iterator
		//  * 
		//  */
		// virtual	~reverse_iterator() {

		// }

		reference	operator[] (difference_type n) {
			return this->base()[-n - 1];
		}
 
		reverse_iterator	&operator++(void) {
			--_it;
			return *this;
		}

		reverse_iterator	&operator--(void) {
			++_it;
			return *this;
		}

		reverse_iterator	operator++(int) {
			reverse_iterator tmp = *this;
			--this->_it;
			return tmp;
		}

		reverse_iterator	operator--(int) {
			reverse_iterator tmp = *this;
			++this->_it;
			return tmp;
		}

		reverse_iterator	operator-(difference_type n) const {
			return reverse_iterator(_it + n);
		}

		reverse_iterator	operator+(difference_type n) const {
			return reverse_iterator(_it - n);
		}

		reverse_iterator	&operator+=(difference_type n){
			this->_it -= n;
			return *this;
		}

		reverse_iterator	&operator-=(difference_type n){
			this->_it += n;
			return *this;
		}

	protected:
		iterator_type	_it;
};
template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	};

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	};


template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs ) {
		return rhs.base() < lhs.base();
	};


template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
		return rhs.base() <= lhs.base();
	};

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs ) {
		return rhs.base() > lhs.base();
	};

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ) {
		return rhs.base() >=	 lhs.base();
	};

template< class Iterator>
reverse_iterator<Iterator>
    operator+( typename ft::reverse_iterator<Iterator>::difference_type n,
               const ft::reverse_iterator<Iterator>& it ) {
				return it + n;
	};

template< class Iterator>
typename reverse_iterator<Iterator>::difference_type
    operator-( typename ft::reverse_iterator<Iterator>::difference_type n,
               const ft::reverse_iterator<Iterator>& it ) {
				return it - n;
	};

	template< class L, class R>
	typename reverse_iterator<L>::difference_type operator-(const ft::reverse_iterator<L>& lhs,  const ft::reverse_iterator<R>& rhs ) 
	{
			return rhs.base() - lhs.base() ;
	};

}
#endif
