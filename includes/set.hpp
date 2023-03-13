#ifndef SET_HPP
#define SET_HPP
#include "map.hpp"
namespace ft{

	template<
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	> class set{
		public:

		typedef Key					key_type;
		typedef Key					value_type;
		typedef Compare				key_compare;
		typedef Compare				value_compare;
		typedef Allocator			allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type          					size_type;
		typedef typename ft::RedBlackTree<key_type, value_type, key_compare>::iterator	iterator;
		typedef typename ft::RedBlackTree<key_type, value_type, key_compare, ft::is_const<value_type>::value >::iterator	const_iterator;
		typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename iterator::difference_type								difference_type;
		typedef typename iterator::iterator_category							iterator_category;
		
      
		explicit set( const Compare& comp = Compare(),const Allocator& alloc = Allocator() ) : alloc(alloc), comp(comp)
		{

		}

		template< class InputIt > set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : alloc(alloc), comp(comp) {
				this->insert(first, last);
		}
		set( const set& other ) : alloc(other.alloc), comp(other.comp) {
			this->insert(other.begin(), other.end());
		}
		~set() {
			this->clear();
			this->_data.deleteSentinel();
		}

		size_type erase(const key_type& k)
		{
			iterator it = find(k);
			if (it != this->end())
			{
				this->_data.deletion(k);
				return 1;
			}
			return 0;
		}

				size_type size(void) const
		{
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
		}
		void erase( iterator pos )
		{
			this->erase(*pos);
		}
		void	erase(iterator first, iterator last)
		{
			while(first != last)
			{
				this->erase((*(first++)));
			}
		}

		pair<iterator, bool>	insert(const key_type& k)
		{
			return (this->_data.insert(k));
		}

		iterator	insert(iterator pos, key_type k)
		{
			(void)pos;
			return (this->_data.insert(k).first);
		}

		template<class InputIt>
		void	insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr_t)
		{
			difference_type n = ft::distance(first, last);
			for (; n > 0; n--, first++)
				this->insert(*first);
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
				if (comp(key, *it))
					return it;
			return end();
		}

		iterator	lower_bound(const key_type& key)
		{

			for (iterator it = begin(); it != end(); it++)
				if (!comp(*it, key))
					return it;
			return end();
		}

		const_iterator	upper_bound(const key_type& key) const
		{

			for (const_iterator it = begin(); it != end(); it++)
				if (comp(key, *it))
					return it;
			return end();
		}

		const_iterator	lower_bound(const key_type& key) const
		{

			for (const_iterator it = begin(); it != end(); it++)
				if (!comp(*it, key))
					return it;
			return end();
		}

		
		size_type count(key_type key) const
		{
			iterator it = find(key);
			if (it != end())
				return 1;
			return 0;
		}

		iterator	find (const key_type& k)
		{
		
			return iterator( this->_data.searchPair(k), this->_data.getValue());
		}
		
		const_iterator	find (const key_type& k) const
		{
			return const_iterator(  this->_data.searchPair(k), this->_data.getValue());
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
			return key_compare();
		}

		void swap (set& x)
			{
				if (x == *this)
					return;
				key_compare		tmp_comp = x.comp;
				allocator_type	tmp_alloc = x.alloc;
				ft::RedBlackTree<key_type, value_type, key_compare> tmp_data = x._data;

				x._data = this->_data;
				x.comp = this->comp;
 				x.alloc = this->alloc;

				this->_data = tmp_data;
				this->alloc = tmp_alloc;
				this->comp = tmp_comp;
			}
		
		private:
			allocator_type	alloc;
			key_compare		comp;
			ft::RedBlackTree<key_type, value_type, key_compare> _data;

	};

	template< typename T, typename Alloc >
bool operator==( const ft::set<T, Alloc>& lhs,
                 const ft::set<T, Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

template< typename T, typename Alloc >
bool operator!=( const ft::set<T, Alloc>& lhs,
                 const ft::set<T, Alloc>& rhs ) {
		return !(lhs == rhs);		
	};


template< typename T, typename Alloc >
bool operator<( const ft::set<T, Alloc>& lhs,
                const ft::set<T, Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};


template< typename T, typename Alloc >
bool operator<=( const ft::set<T, Alloc>& lhs,
                 const ft::set<T, Alloc>& rhs ) {
		return !(rhs < lhs);
	};

template< typename T, typename Alloc >
bool operator>( const ft::set<T, Alloc>& lhs,
                const ft::set<T, Alloc>& rhs ) {
		return rhs < lhs;
	};

template< typename T, typename Alloc >
bool operator>=( const ft::set<T, Alloc>& lhs,
                 const ft::set<T, Alloc>& rhs ) {
		return !(lhs < rhs);
	};

}
#endif
