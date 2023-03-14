#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "utilities.hpp"
#include <iterator>
#include "rbt_map.hpp"

namespace ft
{
	template <typename T>
	class bidirectional_iterator{
		public:

			typedef typename Iterator<std::bidirectional_iterator_tag, T>::value_type	    	value_type;
			typedef typename Iterator<std::bidirectional_iterator_tag, T>::pointer 				pointer;
			typedef typename Iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename Iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename Iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		bidirectional_iterator() : _p (nullptr_t) {

		}
		~bidirectional_iterator() {

		}
		bidirectional_iterator(pointer p) : _p(p) {

		}

		bidirectional_iterator(const bidirectional_iterator &a) : _p(a._p){

			
		}
		bidirectional_iterator&	operator=(const bidirectional_iterator &a) {
			if (a._p != NULL)
			{
				this->_p = a._p;
			}
			return (*this);
		}

		reference	operator*(void) const {
			return (this->_p->data);
		}
		pointer	operator->(void) {
			return (&(this->operator*()));
		}
		bidirectional_iterator &operator++(void) {
			_p++;
			return (*this);
		}
		bidirectional_iterator	operator++(int) {
			bidirectional_iterator tmp (*this);
			++this->_p;
			return (tmp);
		}
		bidirectional_iterator	&operator--(void) {
			_p--;
			return (*this);
		}
		bidirectional_iterator	operator--(int) {
			bidirectional_iterator tmp (*this);
			--this->_p;
			return (tmp);
		}

		private:
			pointer _p;
	};

	template<typename T, typename Node, class Compare>
	class tree_iterator : public ft::bidirectional_iterator<T> {
			
		public:
			typedef typename Iterator<std::bidirectional_iterator_tag, T>::value_type	    	value_type;
			typedef Node	node_type;
			typedef typename Iterator<std::bidirectional_iterator_tag, value_type>::pointer 			pointer;
			typedef typename Iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename Iterator<std::bidirectional_iterator_tag, node_type>::pointer 				node_pointer;
			typedef typename Iterator<std::bidirectional_iterator_tag, node_type>::reference			node_reference;
			typedef typename Iterator<std::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename Iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

			tree_iterator(const Compare& cmp = Compare()) : _p(), _TNULL(), _cmp(cmp){
			}

			tree_iterator(node_pointer node, node_pointer TNULL, const Compare& cmp = Compare() ) : _p(node), _TNULL(TNULL), _cmp(cmp){

			}
		
			tree_iterator(const tree_iterator<typename ft::remove_const<T>::type, Node, Compare> & a) : _p(a.getP()), _TNULL(a.getNULL()), _cmp(a.getComp()) {

			}
			tree_iterator &operator=(const tree_iterator<typename ft::remove_const<T>::type, Node, Compare> &a)
			{
				if (*this == a)
					return *this;
				this->_p = a._p;
				this->_TNULL = a._TNULL;
				this->_cmp = a._cmp;

				return *this;
			}
			
			reference operator*(void) const
			{
				return this->_p->data;
			}
			pointer operator->(void) const
			{
				return &(operator*());
			}

			tree_iterator&	operator++(void)
			{
				this->_p = successor(_p);
				return *this;
			}

			tree_iterator&	operator--(void)
			{
				this->_p = predecessor(_p);
				return *this;
			}
			tree_iterator operator++(int)
			{
				tree_iterator tmp (*this);
				++(*this);
				return tmp;
	
			}

			tree_iterator operator--(int)
			{
				tree_iterator tmp (*this);
				--(*this);
				return tmp;
	
			}

			node_pointer	getPointer(void) const{
				return this->_p;
			}
			// void	isNULL()
			// {
			// 	if (_p->left == _TNULL)
			// 		std::cout << "Yes" << std::endl;
			// 	if (_p == _TNULL)
			// 		std::cout << "I am sentinel" << std::endl;
			// }

			bool	operator==(const tree_iterator &a)
			{
				return this->_p == a._p;
			}

			bool	operator!=(const tree_iterator& a)
			{
				return this->_p != a._p;
			}
	
			virtual ~tree_iterator() {
			}

			/** copy paste from rbt
			 */
			node_pointer rightNav(node_pointer _p)
			{
				if (!_p)
					return nullptr_t;
				while (_p->right != _TNULL)
					_p = _p->right;
				return _p;
			}

			node_pointer leftNav(node_pointer _p)
			{
				if (!_p)
					return nullptr_t;
				while (_p->left != _TNULL)
					_p = _p->left;
				return _p;
			}
			/**find the right most left subtree
			 1. check left of the node see if it is TNULL
			 2. if it exist, then move to the left node and keep moving right from there until the end
			 3. if it doesn't exist, check if the given node is left node of its parent
			 3.a if the condition fullfilled, move up one node and check for its condition again until the node isn't left node of its parent
			 	while updating predecessor being the parent node as it traverse
			 4. if all else failed, return nulltpr **/
			node_pointer	predecessor (node_pointer node)
			{
				node_pointer pred = _TNULL;
				if (node == _TNULL)
					return node->right;
				if (node->left == _TNULL)
				{
					if (node != _TNULL->left)
					{
						pred = node->parent;
							for (;pred != _TNULL && node == pred->left; node = pred)
								pred = pred->parent;
					}
				}
				else
					return (node->rightNav(node->left, _TNULL));
				return pred;
				
			}
			/**find the left most right subtree
			 1. check right of the node see if it is TNULL
			 2. if it exist, then move to the right node and keep moving left from there until the end
			 3. if it doesn't exist, check if the given node is right node of its parent
			 3.a if the condition fullfilled, move up one node and check for its condition again until the node isn't right node of its parent
			 	while updating successor being the parent node as it traverse
			 4. if all else failed, return nulltpr **/
			node_pointer	successor(node_pointer node)
			{
				// std::cout << node->data.first << std::endl;
				node_pointer succ = _TNULL;
				if (node == _TNULL)
					return node->left;
				if (node->right == _TNULL)
				{
					// std::cout << "here 1";
					if (node != _TNULL->right)
					{
						succ = node->parent;
						// std::cout <<"============"  << succ->data.first  << "==" << succ->left->data.first << std::endl;
							while( succ != _TNULL && node == succ->right)
							{
								node = succ;
								succ = succ->parent;
							}
							// std::cout << "here 3";
					}
				}
				else
				{
					// std::cout << "here 2";
					return (node->leftNav(node->right, _TNULL));
				}
				return succ;
			}
			node_pointer	predecessor2(node_pointer node)
			{
				node_pointer pred = _TNULL;
				if (node == _TNULL)
					return node->left;
				if (node == _TNULL->left)
					return _TNULL;
				if (node->left != _TNULL)
				{
					pred = node->left;
					return (rightNav(pred));
				}
				pred = node->parent;
				for (;pred != _TNULL && node == pred->left; node = pred)
					pred = pred->parent;
				return pred;
			}
			node_pointer	successor2(node_pointer node)
			{
				node_pointer succ = _TNULL;
				if (node == _TNULL)
					return node->left;
				if (node == _TNULL->right)
					return _TNULL;
				if (node->right != _TNULL)
				{
					succ = node->right;
					return (leftNav(succ));
				}
				succ = node->parent;
				for (;succ != _TNULL && node == succ->right; node = succ)
					succ = succ->parent;
				return succ;
			}

			node_pointer getP() const
			{
				return this->_p;
			}

			node_pointer getNULL() const
			{
				return this->_TNULL;
			}
			Compare	getComp() const
			{
				return this->_cmp;
			}
		private:
			node_pointer	_p;
			node_pointer	_TNULL;
			Compare _cmp;
	};

} // namespace ft


#endif
