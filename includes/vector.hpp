#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <cstddef>
// #include <tgmath.h>

#include "./utils/random_access_iterator.hpp"
#include "./utils/reverse_iterator.hpp"

namespace	ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T			value_type;
		
			typedef Allocator allocator_type;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef	typename ft::random_access_iterator<value_type>	iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>	reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename allocator_type::size_type		size_type;
			typedef typename ft::random_access_iterator<value_type>::difference_type	difference_type;
			
			/**
			 * @brief default construct when no parameter is given
			 * 
			 * @param alloc if allocator was given, initialize class with the given allocator
			 * explicit so that it cannot be used in inplicit conversion
			 */
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0),_data(nullptr_t)
			{
				// std::cout << "vector class created" << std::endl;
			};
			~vector() {
				_alloc.deallocate(_data, _capacity);
				// std::cout << "vector class destructed" << std::endl;
			};


			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n){
				
				if (n > this->max_size())
					throw std::out_of_range("exceed maximum range");
				this->_data = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(this->_data + i,  val);
			};

			template<class InputIt>
			vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr_t) : _alloc(alloc)
			{
				difference_type n = std::distance(first, last);
				if (n > this->max_size())
					throw std::out_of_range("exceed maximum range");
				this->_data = _alloc.allocate(n);
				this->_size = n;
				this->_capacity = n;
				for (size_type i = 0; n > 0; n--, i++, first++)
					_alloc.construct(this->_data + i, *first);
			}
			
			vector(const vector& x) : _alloc(x._alloc), _size(x.size()), _capacity(x.capacity())
			{
				if (x.size() > this->max_size())
					throw std::out_of_range("exceed maximum range");
				this->_data = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					this->_data[i] = x._data[i];
			};

			allocator_type	get_allocator(void) const
			{
				return this->_alloc;
			}
			vector&		operator=(const vector& x)
			{
				this->_size = x.size();
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				this->_data = _alloc.allocate(this->_size);
				for (size_type i = 0; i < this->_size; i++)
					this->_data[i] = x._data[i];
				return (*this);
			};

			reference	operator[](const size_type pos)
			{
				return*(this->_data + pos);
			};

			const_reference	operator[](const size_type pos) const
			{
				return*(this->_data + pos);
			};
			
			pointer	getPointer(void){
				return (this->_data);
			};

			void assign(size_type count, const value_type& value)
			{
				if (count > this->max_size())
					throw std::out_of_range("exceed maximum range");
				reserveAlgo(count);
				for (size_type i = 0; i < count; i++)
					this->_data[i] = value;
				this->_size = count;
			};

			template<class InputIt>
			void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr_t)
			{
				size_type count = std::distance(first, last);
				if (count > this->max_size())
					throw std::out_of_range("exceed maximum range");
				reserveAlgo(count);
				for (size_type i = 0; i < count;first++, i++)
					_alloc.construct(_data + i , *(first));
				this->_size = count;
			};

			void	reserveAlgo(size_type count)
			{
				if (count> capacity())
				{
					size_type new_cap = capacity() * 2;
					if (count > new_cap)
						reserve(count);
					else
						reserve(new_cap);
				}
			}

			iterator	begin(void){
				return iterator(this->_data);
			};

			iterator	end(void){
				return iterator(this->_data + _size);
			};

			const_iterator	begin(void) const {
				return const_iterator(this->_data);
			};

			const_iterator	end(void) const {
				return const_iterator(this->_data + _size);
			};

			reverse_iterator	rbegin(void){
				return reverse_iterator(this->end());
			};

			reverse_iterator	rend(void){
				return reverse_iterator(this->begin());
			};

			const_reverse_iterator	rbegin(void) const {
				return reverse_iterator(this->end());
			};

			const_reverse_iterator	rend(void) const {
				return reverse_iterator(this->begin());
			};
			//Capacity member function
			
			size_type capacity(void) const	{
				return (this->_capacity);
			};
			bool	empty(void) const {
				if (begin() == end())
					return (true);
				return (false);
			};

			size_type size(void) const {
				return (this->_size);
			};

			void	reserve(size_type new_cap)	{
				
				if (new_cap > this->max_size())
					throw std::out_of_range("exceed maximum range");
				if (new_cap < this->_capacity)
					return ;
				pointer block = this->_alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(block + i, at(i));
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_data = block;
				this->_capacity = new_cap;
			};

			reference	at(size_type pos)
			{
				if (pos >= size())
					throw std::out_of_range("pos is out of range");
				return *(this->_data + pos);
			};
			const_reference	at(size_type pos) const
			{
				if (pos >= size())
					throw std::out_of_range("pos is out of range");
				return *(this->_data + pos);
			};
			reference	front(void)
			{
				return *(this->_data);
			};

			const_reference	front(void) const
			{
				return *(this->_data);
			};

			reference	back(void)
			{
				return *(this->_data + size() - 1);
			};

			const_reference back(void) const
			{
				return *(this->_data + size() - 1);
			};

			value_type	*data(void)
			{
				return (this->_data);
			};

			const value_type* data(void) const 
			{
				// std::cout << "const called" << std::endl;
				return (this->_data);
			};

			//Modifiers

			size_type max_size() const{
				return (_alloc.max_size());
			}

			void	clear	(void)
			{
				for (; _size > 0; --_size)
					_alloc.destroy(_data + _size);
			
			};

			void	push_back(const value_type n)
			{
				// std::cout << "current size is :" << _size << std::endl;
				if (_size + 1 > _capacity)
					reserve(_size + 1);
				*(this->_data + _size) = n;
				_size++;
			};

			void	pop_back(void)
			{
				_alloc.destroy(&this->back());
				this->_size--;
			};

			iterator erase (iterator position)
			{
				// if (*position == NULL)
				// 	throw std::out_of_range("pos is out of range");
				pointer	tmp = position.getPointer(); ;
				size_type	count = end() - position - 1;
				_alloc.destroy(position.getPointer());
				if (count > 1)
				{
					for (int i = 0 ; count > 0; count--, i++)
					{
						_alloc.construct(position.getPointer() + i, *(position + i + 1));
						_alloc.destroy(position.getPointer() + i + 1);
					}
				}
				_size--;
				return iterator(tmp);
			
			};

			iterator erase (iterator first, iterator last)
			{
				// std::cout << "range" << range << std::endl;
				pointer	tmp = first.getPointer();
				// size_type diff = std::distance(first, last);
				
				for (; first != last; first++)
					_alloc.destroy(first.getPointer());
				size_type count = end() - last;
				for (int i = 0 ; count > 0; count--, i++)
				{
					_alloc.construct(tmp + i, *(last.getPointer() + i));
					_alloc.destroy(last.getPointer() + i);
				}
				_size -= last.getPointer() - tmp;
				return iterator(tmp);
			};
			
			iterator insert(iterator pos, const value_type& value)
			{
				// std::cout << "pos value is" << *pos << std::endl;
				size_type t_pos = pos.getPointer() - begin().getPointer();
				if (t_pos > this->size())
					throw std::out_of_range("exceed maximum range");
				size_type count = size() + 1 - t_pos;
				if (size() + 1 > capacity())
					reserveAlgo(size() + 1);

				// std::cout << t_pos << count << std::endl;
				size_type i = 0;
				for (iterator it = this->end() - 1; i < count; i++, it--)
				{	
					// std::cout << *it << "&&" << i << std::endl;
					_alloc.construct((it + 1).getPointer(), *(it));
				}
				_alloc.construct(this->_data + t_pos, value);
				// std::cout << *pos << std::endl;
				this->_size += 1;
				return iterator(this->_data + t_pos);
			};

			void insert(iterator pos, size_type count, const value_type& value)
			{
				// std::cout << "pos value is" << *pos << std::endl;
				size_type t_pos = pos.getPointer() - begin().getPointer();
				if (t_pos > this->size())
					throw std::out_of_range("exceed maximum range");
				size_type distance = size() + 1 - t_pos;
				if (size() + count > capacity())
					reserveAlgo(size() + count);
				// std::cout << t_pos << count << std::endl;
				size_type i = 0;
				for (iterator it = this->end() - 1; i < distance; i++, it--)
				{	
					// std::cout << *it << "&&" << i << std::endl;
					_alloc.construct((it + count).getPointer(), *(it));
				}
				for (size_type i = 0; i < count; i++)
					_alloc.construct(this->_data + t_pos + i, value);
				// std::cout << *pos << std::endl;
				this->_size += count;
			};
			
			template<class InputIt>
			void insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr_t)
			{
				// std::cout << "pos value is" << *pos << std::endl;
				
				size_type t_pos = pos.getPointer() - begin().getPointer();
				if (t_pos > this->size())
					throw std::out_of_range("exceed maximum range");
				size_type distance = size() + 1 - t_pos;
				size_type count = std::distance(first, last);
				if (count > this->max_size())
					throw std::out_of_range("exceed maximum range");
				reserveAlgo(size() + count);
				// std::cout << t_pos << count << std::endl;
				size_type i = 0;
				for (iterator it = this->end() - 1; i < distance; i++, it--)
				{	
					// std::cout << *it << "&&" << i << std::endl;
					_alloc.construct((it + count).getPointer(), *(it));
				}
				for (size_type i = 0; first != last; first++, i++)
					_alloc.construct(this->_data + t_pos + i, *first);
				// std::cout << *pos << std::endl;
				this->_size += count;
			};


			void resize(size_type count, value_type value=value_type()){
			if (count > size())
				insert(end(), count, value);
			if (count < size())
			{
				size_type n = size();
					for (; n > count; n--)
					_alloc.destroy(this->_data + n);
				_size = n;

			}
			}
			void swap (vector& x)
			{
				if (x == *this)
					return;
				pointer 	tmp_data = x._data;
				size_type	tmp_size = x._size;
				size_type	tmp_capacity = x._capacity;
				Allocator	tmp_alloc = x._alloc;

				x._data = this->_data;
				x._size = this->_size;
				x._capacity = this->_capacity;
				x._alloc = this->_alloc;

				this->_data = tmp_data;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_alloc = tmp_alloc;
			}
			// Vector(const Vector &a);
			// Vector&	operator=(const Vector&a);

		private:
			Allocator	_alloc;
			size_type	_size;
			size_type	_capacity;
			pointer		_data;
				
	};

	template< typename T, typename Alloc >
bool operator==( const ft::vector<T, Alloc>& lhs,
                 const ft::vector<T, Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

template< typename T, typename Alloc >
bool operator!=( const ft::vector<T, Alloc>& lhs,
                 const ft::vector<T, Alloc>& rhs ) {
		return !(lhs == rhs);		
	};


template< typename T, typename Alloc >
bool operator<( const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};


template< typename T, typename Alloc >
bool operator<=( const ft::vector<T, Alloc>& lhs,
                 const ft::vector<T, Alloc>& rhs ) {
		return !(rhs < lhs);
	};

template< typename T, typename Alloc >
bool operator>( const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs ) {
		return rhs < lhs;
	};

template< typename T, typename Alloc >
bool operator>=( const ft::vector<T, Alloc>& lhs,
                 const ft::vector<T, Alloc>& rhs ) {
		return !(lhs < rhs);
	};

template< class T >
void swap( vector<T>& a, vector<T>& b )
{
	a.swap(b);
}
	// template <class T,class Allocator = std::allocator<T> >
	// std::ostream&	operator<< (std::ostream &os, ft::vector<T> &a)
	// {
	// 	return os << a;
	// }

};


#endif
