#ifndef FORWARD_ITERATOR_HPP
#define FORWARD_ITERATOR_HPP

#include "utilities.hpp"

namespace	ft
{
	template <
	class Category, 
	class T,
    class Distance = std::ptrdiff_t,
    class Pointer = T*,
    class Reference = T&
>
class forward_iterator : public Iterator<std::input_iterator_tag, T>{
	public:

		forward_iterator() : _p (nullptr_t) {

		}
		~forward_iterator() {

		}
		forward_iterator(pointer p) : _p(p) {

		}

		forward_iterator(const forward_iterator &a) : _p(a._p){

			// std::cout << "forward_iterator copy constructor called" << std::endl;
		}
		forward_iterator&	operator=(const forward_iterator &a) {
			if (a._p != NULL)
			{
					this->_p = a._p;
					// std::cout << "forward_iterator copy assignment called" << std::endl;
			}
		return (*this);
		}
		forward_iterator &operator++(void) {
			_p++;
			return (*this);
		}
		forward_iterator	operator++(int) {
			forward_iterator tmp (*this);
			++this->_p;
			return (tmp);
		}
	private:
		pointer _p;
};
}
#endif
