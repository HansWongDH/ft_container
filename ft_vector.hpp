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
			size_t	size;
			size_t	capacity;
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

			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), size(), _data()
			{
				std::cout << "vector class created" << std::endl;
			}
			~vector() {
				// _alloc.deallocate(_data);
				std::cout << "vector class destructed" << std::endl;
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), size(n) {
				this->_data = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_data[i] = val;
			}

			vector(const vector& x) : size(x.size), _alloc(x._alloc)
			{
				this->_data = _alloc.allocate(size);
				for (size_type i = 0; i < size; i++)
					this->_data[i] = x._data[i];
			}

			vector&		operator=(const vector& x)
			{
				this->size = x.size;
				this->_alloc = x._alloc;
				this->_data = _alloc.allocate(size);
				for (size_type i = 0; i < size; i++)
					this->_data[i] = x._data[i];
				return (*this);
			}

			void assign(size_type count, const value_type& value)
			{
				for (size_type i = 0; i < count; i++)
					this->_data[i] = value;
			}

			template<class InputIt>
			void assign(InputIt first, InputIt last)
			{
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
				return iterator(this->_data + size);
			}

			const_iterator	begin(void) const {
				return const_iterator(this->_data);
			}

			const_iterator	end(void) const {
				return const_iterator(this->_data + size);
			}

			// Vector(const Vector &a);
			// Vector&	operator=(const Vector&a);
	};
};

#endif
