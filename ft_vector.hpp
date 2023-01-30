#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include "ft_iterator.tpp"

namespace	ft
{
	template <class T,class Allocator = std::allocator<T> >
	class vector
	{
		private:
			T	*_data;
			size_t	_size;
			size_t	_capacity;
			Allocator	_alloc;

		public:
			typedef T			value_type;
			typedef size_t		size_type;
			typedef Allocator allocator_type;
			typedef T*	 pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef	random_access_iterator<value_type>	iterator;
			typedef	random_access_iterator<const value_type>	const_iterator;

			// typedef retarded_const_iterator		const_iterator;
			// typedef retarded_reverse_iterator	reverse_iterator;
			// typedef	const_retarded_reverse_iterator	const_reverse_iterator;

			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(), _data(), _capacity()
			{
				std::cout << "vector class created" << std::endl;
			}
			~vector() {
				// _alloc.deallocate(_data);
				std::cout << "vector class destructed" << std::endl;
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n){
				this->_data = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_data[i] = val;
			}

			vector(const vector& x) : _size(x.size), _alloc(x._alloc)
			{
				this->_data = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					this->_data[i] = x._data[i];
			}

			vector&		operator=(const vector& x)
			{
				this->_size = x.size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				this->_data = _alloc.allocate(this->_size);
				for (size_type i = 0; i < this->_size; i++)
					this->_data[i] = x._data[i];
				return (*this);
			}

			reference	operator[](const size_type pos)
			{
				return*(this->_data + pos);
			}

			void assign(size_type count, const value_type& value)
			{
				if (count > capacity())
				{
					size_type new_cap = capacity() * 2;
					if (count > new_cap)
						reserve(new_cap + (count - new_cap));
					else
						reserve(new_cap);
				}
				for (size_type i = 0; i < count; i++)
					this->_data[i] = value;
				this->_size = count;
			}

			template<class InputIt>
			void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr)
			{
				size_type	count = 0;
				for (InputIt copy = first; copy != last; copy++)
					count++;
				if (count > capacity())
				{
					size_type new_cap = capacity() * 2;
					if (count > new_cap)
						reserve(new_cap + (count - new_cap));
					else
						reserve(new_cap);
				}
				for (;first != last; first++)
				{
					*(this->_data) = *first;
					this->_data++;
				}
			}

			iterator	ft_iterator(void){
				return iterator(this->_data);
			}

			iterator	begin(void){
				return iterator(this->_data);
			}

			iterator	end(void){
				return iterator(this->_data + _size);
			}

			const_iterator	begin(void) const {
				return const_iterator(this->_data);
			}

			const_iterator	end(void) const {
				return const_iterator(this->_data + _size);
			}

			size_type capacity(void) const	{
				return (this->_capacity);
			}

			void	reserve	(size_type new_cap)	{
	
				if (new_cap < this->_capacity)
					return ;
				T	*block = this->_alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; i++)
					block[i] = this->_data[i];
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_data = block;
				this->_capacity = new_cap;
			}

			// Vector(const Vector &a);
			// Vector&	operator=(const Vector&a);
	};
};

#endif
