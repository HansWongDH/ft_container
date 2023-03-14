#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <stdexcept>
#include "./utils/utilities.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/rbt_map.hpp"
#include "./utils/bidirectional_iterator.hpp"
// #include <memory>

using std::cout;
using std::endl;

namespace	ft
{

	template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
> class map{
    public:

		
            typedef Key                                         							key_type;
            typedef T                                           							mapped_type;
            typedef ft::pair<const key_type, mapped_type>             					value_type;
            typedef Compare                                     					key_compare;
            typedef Allocator                                 						allocator_type;
            typedef typename allocator_type::reference          					reference;
            typedef typename allocator_type::const_reference   						const_reference;
            typedef typename allocator_type::pointer            					pointer;
            typedef typename allocator_type::const_pointer      					const_pointer;
            typedef typename allocator_type::size_type          					size_type;

			class value_compare
		{
			private:
				key_compare c;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool	result;
			
			public:

				value_compare(key_compare com = key_compare()) : c(com) {

				}
				bool operator()( const value_type &lhs, const value_type& rhs ) const
				{
					return (c(lhs.first, rhs.first));
				}
		};
            typedef typename ft::RedBlackTree<value_type, value_compare>::iterator	iterator;
			typedef typename ft::RedBlackTree<value_type, value_compare>::const_iterator	const_iterator;
			typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename iterator::difference_type								difference_type;
			typedef typename iterator::iterator_category							iterator_category;
      

		/**
		 * @brief refer std::less class structure
		 * 
		 */
		
		explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : alloc(alloc), comp(comp), _data()
		{
		}
		
		map( const map& other ) : alloc(other.alloc), comp(other.comp), _data(other._data)
		{
		}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(), 
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr_t) : alloc(alloc), comp(comp)
		{
			this->clear();
			this->insert(first, last);
		}


        ~map() {
			this->clear();
			// this->_data.deleteSentinel();
		}

    	pair<iterator, bool>	insert(const value_type& k)
		{
			return (this->_data.insert(k));
		}

		iterator	insert(iterator pos, value_type k)
		{
			(void)pos;
			return (this->_data.insert(k).first);
		}

		template<class InputIt>
		void	insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr_t)
		{
			// if(!ft::iterator_traits<InputIt>::iterator_category == iterator_category )
			// 	std::cout << "HEHE" << std::endl;
			difference_type n = ft::distance(first, last);
			for (; n > 0; n--, first++)
				this->insert(*first);
		}

		map& operator=(const map& other)
		{

			if (this == &other)
				return *this;
			this->clear();
			this->alloc = other.alloc;
			this->comp = other.comp;
			this->_data = other._data;
			return *this;
		}
		
		size_type erase(const key_type& k)
		{
			iterator it = find(k);
			if (it != this->end())
			{
				this->_data.deletion(ft::make_pair(k, mapped_type()));
				return 1;
			}
			return 0;
		}

		void erase( iterator pos )
		{
			this->erase(pos->first);
		}
		void	erase(iterator first, iterator last)
		{
			iterator it = first;
			while(first != last)
			{
				// std::cout << (*first).first << std::endl;
				this->erase((*(first++)).first);
			}
		}

		size_type size(void) const
		{
			// cout << "begin :" <<  begin()->first << endl;
			// cout << "end  :" <<  end()->first << endl;
			return ft::distance(begin(), end());
		}

		bool	empty(void) const
		{
			if (begin() == end())
				return true;
			return false;
		}

		size_type max_size() const{
			return (this->_data.maxsize());
		}

		void clear(void)
		{
			this->_data.fullDelete();
			// cout << "clear size : " << size() << endl;
		}
		// void	test(const key_type k)
		// {
		// 	this->this->_data.search(ft::make_pair(k, mapped_type()));
		// }



		iterator	find (const key_type& k)
		{
		
			return iterator( this->_data.searchPair(ft::make_pair(k, mapped_type())), this->_data.getValue());
		}
		
		const_iterator	find (const key_type& k) const
		{
			return const_iterator(  this->_data.searchPair(ft::make_pair(k, mapped_type())), this->_data.getValue());
		}

		void	print(void)
		{
			 this->_data.printTree();
		}


		mapped_type&	operator[](const key_type& k)
		{
				return (*(this->insert(ft::make_pair(k, mapped_type()))).first).second;
		}

		mapped_type&	at(const key_type& key) const
		{
			if (find(key) == end())
				throw std::out_of_range("key is out of range");
			return *(find(key)).second;
		}
        iterator    begin(void)
        {
            return iterator(this->_data.getValue()->left, this->_data.getValue());
        }

        iterator    end(void)
        {
            return iterator(this->_data.getValue(), this->_data.getValue());
        }

		const_iterator    begin(void) const
        {
            return const_iterator(this->_data.getValue()->left, this->_data.getValue());
        }

        const_iterator    end(void) const
        {
            return const_iterator(this->_data.getValue(), this->_data.getValue());
        }

		reverse_iterator	rbegin(void)
		{
			return reverse_iterator(this->end());
		}
		
		reverse_iterator	rend(void)
		{
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator	rbegin(void) const
		{
			return reverse_iterator(this->end());
		}

	
		const_reverse_iterator	rend(void) const
		{
			return reverse_iterator(this->begin());
		}

		iterator	upper_bound(const key_type& key)
		{

			for (iterator it = begin(); it != end(); it++)
				if (comp(key, it->first))
					return it;
			return end();
		}

		iterator	lower_bound(const key_type& key)
		{

			for (iterator it = begin(); it != end(); it++)
				if (!comp(it->first, key))
					return it;
			return end();
		}

		const_iterator	upper_bound(const key_type& key) const
		{

			for (const_iterator it = begin(); it != end(); it++)
				if (comp(key, it->first))
					return it;
			return end();
		}

		const_iterator	lower_bound(const key_type& key) const
		{

			for (const_iterator it = begin(); it != end(); it++)
				if (!comp(it->first, key))
					return it;
			return end();
		}

		size_type count(key_type key) const
		{
			if (find(key) != end())
				return 1;
			return 0;
		}

		ft::pair<iterator, iterator> equal_range(const key_type& key)
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}
		
		key_compare key_comp(void) const
		{
			return key_compare();
		}
		
		value_compare value_comp(void) const
		{
			return value_compare(comp);
		}

		
		void swap (map& x)
			{
				if (&x == this)
					return;
				// key_compare		tmp_comp = x.comp;
				// allocator_type	tmp_alloc = x.alloc;
				// ft::RedBlackTree<key_type, value_type, value_compare> tmp_data = x._data;
				
				// x._data = this->_data;
				// x.comp = this->comp;
 				// x.alloc = this->alloc;

				// this->_data = tmp_data;
				// this->alloc = tmp_alloc;
				// this->comp = tmp_comp;
				std::swap(this->alloc, x.alloc);
				std::swap(this->comp, x.comp);
				this->_data.swap(x._data);
			}
		
    private:
    
        allocator_type alloc;
		key_compare comp;
		RedBlackTree<value_type, value_compare> _data;
		
};
	template< typename Key, typename T, typename Alloc >
	bool operator==( const ft::map<Key, T, Alloc>& lhs,
					const ft::map<Key, T, Alloc>& rhs ) {
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		};

	template< typename Key, typename T, typename Alloc >
	bool operator!=( const ft::map<Key, T, Alloc>& lhs,
					const ft::map<Key, T, Alloc>& rhs ) {
			return !(lhs == rhs);		
		};


	template< typename Key, typename T, typename Alloc >
	bool operator<( const ft::map<Key, T, Alloc>& lhs,
					const ft::map<Key, T, Alloc>& rhs ) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		};


template< typename Key, typename T, typename Alloc >
bool operator<=( const ft::map<Key, T, Alloc>& lhs,
                 const ft::map<Key, T, Alloc>& rhs ) {
		return !(rhs < lhs);
	};

template< typename Key, typename T, typename Alloc >
bool operator>( const ft::map<Key, T, Alloc>& lhs,
                const ft::map<Key, T, Alloc>& rhs ) {
		return rhs < lhs;
	};

template< typename Key, typename T, typename Alloc >
bool operator>=( const ft::map<Key, T, Alloc>& lhs,
                 const ft::map<Key, T, Alloc>& rhs ) {
		return !(lhs < rhs);
	};
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key, T, Compare, Alloc>& lhs,ft::map<Key, T, Compare, Alloc>& rhs )
	{
		return lhs.swap(rhs);
	};
}

#endif
