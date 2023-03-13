#ifndef RBT_MAP_HPP
#define RBT_MAP_HPP

#include <iostream>
#include <memory>
#include "utilities.hpp"
#include "bidirectional_iterator.hpp"


namespace ft
{
	
	
	
	/*when initialize a tree, its left and right is equal = nullptr_t, but to further differentiate its property, a node TNULL is created
	 tho emulate NULL for tree*/
    template
    <typename value, typename Key, class Compare = ft::my_less<Key>, bool Cst = false,  typename Allocator = std::allocator<ft::Node<Key> > >
    class RedBlackTree {
        public:
			typedef typename ft::remove_const<Key>::type		key_type;
			typedef Allocator allocator_type;
			typedef ft::Node<key_type>	node;
            typedef ft::Node<key_type>*	nodeptr;
			typedef Compare	key_compare;
			typedef ft::tree_iterator<Key, node, key_compare>	iterator;
			typedef ft::tree_iterator<const Key, node, key_compare>	const_iterator;
			typedef size_t	size_type;

		
            RedBlackTree(const allocator_type& alloc = allocator_type()): _alloc(alloc)
            {
				
				TNULL = _alloc.allocate(1);
				_alloc.construct(TNULL, node(Key(), nullptr_t, TNULL, TNULL));
			
			   root = TNULL;
            }

			 RedBlackTree(Key key, const allocator_type& alloc = allocator_type()): _alloc(alloc)
            {
				TNULL = _alloc.allocate(1);
				_alloc.construct(TNULL, node(key));
			   root = TNULL;
            }

			RedBlackTree(const RedBlackTree& other) : _alloc(other._alloc), _com(other._com), TNULL(other.TNULL), root(other.root)
			{
				// this->TNULL = other.TNULL;
				// this->root = other.root;
				// this->_alloc = other._alloc;
				// this->_com = other._com;
			}

			RedBlackTree& operator=(const RedBlackTree& other)
			{
				this->TNULL = other.TNULL;
				this->root = other.root;
				this->_alloc = other._alloc;
				this->_com = other._com;
				return *this;
			}
            ~RedBlackTree()
            {
				fullDelete();
				deleteSentinel();
            }

			void printHelper(nodeptr root, std::string indent, bool last) 
			{
				if (root != TNULL) 
				{
		
					std::cout << indent;
					if (root == this->root)
						std::cout << "~";
					if (last) 
					{
						std::cout << "R[";
						indent += "   ";
					} 
					else 
					{
						std::cout << "L[";
						indent += "|  ";
					}

					std::string sColor = root->color ? "RED" : "BLACK";
					std::cout << root->data.first << "-"<< root->data.second <<  " ("<< sColor << ")" << "P<" << (root->parent ==  nullptr_t ? 0 : root->parent->data.first)  << ">" << std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
 			 }

			bool equal(const Key &k1, const Key &k2) const
			{
				if (!_com(k1, k2) && !_com(k2, k1))
					return true;
				return false;
			}
			//Create a temp node for right subtree, node->right
			//swap node->right from pointing to right subtree to temp->left;
			//if temp->left is not leaf, point temp->left->parent to node complete the doubly linked list
			//if node->parent is nullptr_t, means it is root and we need to update the root
			//check if node is its parent left or right node and replace that with temp
			void	leftRotate(nodeptr node)
			{
				nodeptr temp;

				temp = node->right;
				node->right = temp->left;
				if (temp->left != TNULL)
					temp->left->parent = node;
				temp->parent = node->parent;
				if (node->parent == nullptr_t)
					root = temp;
				else
					(node->parent->left == node ? node->parent->left : node->parent->right) = temp;
				temp->left = node;
				node->parent = temp;
			}


			//same thing a aboved, jsut everything work in opposite way
			void	rightRotate(nodeptr node)
			{
				nodeptr	temp;

				temp = node->left;
				node->left = temp->right;
				if (temp->right != TNULL)
					temp->right->parent = node;
				temp->parent = node->parent;
				if (node->parent == nullptr_t)
					root = temp;
				else
					(node->parent->left == node ? node->parent->left : node->parent->right) = temp;
				temp->right = node;
				node->parent = temp;
			}

			nodeptr newNode(const Key &key)
			{
				nodeptr n = _alloc.allocate(1);
				_alloc.construct(n, node(key, nullptr_t, TNULL, TNULL));
				n->color = RED;
				return (n);
			}

			size_type	maxsize() const
			{
				return _alloc.max_size();
			}

            ft::pair<iterator, bool> insert(const Key key)
            {

				nodeptr node = newNode(key);
                nodeptr parent = nullptr_t;
                nodeptr leaf = this->root;
				
				/*Navigate through the tree until it find a empty leaf */
				for (; leaf!= TNULL; leaf = (_com(node->data, leaf->data) == 0 ? leaf->right : leaf->left))
				{
					if (equal(leaf->data, node->data))
						return(ft::make_pair(iterator(leaf, TNULL), false));
					parent = leaf;
				}
                node->parent = parent;
                if (parent == nullptr_t)
				{ 
                	root = node;
					node->color = BLACK;
					TNULL->left = root;
					TNULL->right = root;
				}
        		else if (_com(node->data, parent->data)) 
                	parent->left = node;
                else 
                	parent->right = node;
                insertCorrection(node);
				if (_com(node->data, TNULL->left->data))
					TNULL->left = node;
				else if (_com(TNULL->right->data, node->data))
					TNULL->right = node;
				return ft::make_pair(iterator(node, TNULL), true);
            }
			
			/*insert correction will correct the node whenever it violated RBT rule#4 where there cannot have double red
			 This break down two cases based on uncle node, the sibbling node of the node's parent
			 case 1 : if uncle is a red node
			 simply swap the colour of uncle and parent to black and the grandparent to red, to ensure this move doesn't break the rule
			 insert correction get called again
			 case 2 : if uncle is a black node
			 case 2.a : if the node is not aligned with grandparent (namely node being left of parent, parent being left of grandparent)
			 in this case, the node need to perform a leftRotate or rightRotate on parent node to correct it
			 case 2.b : if the node is alligned
			 in this case, the node need to perform leftRotate or rightRotate on grandparent node
			 afterward correct the colour so that the new parent is black while grandpa, which become the inner children after rotate will be red  */
			void	insertCorrection(nodeptr node)
			{

				root->color = BLACK;
				if (node == root || node->parent->color == BLACK)
				{
       				return;
				}
				if(node != root && node->parent->color == RED)
				{
					nodeptr uncle = findUncle(node);
					nodeptr grandpa = findGrandpa(node);
				
					if (uncle && uncle->color == RED)
					{
						uncle->color = BLACK;
						node->parent->color = BLACK;
						grandpa->color = RED;
						// std::cout << "here2 node key is :" << node->data.first << std::endl;
						// std::cout << "here2 uncle node key is :" << node->data.first << std::endl;
						insertCorrection(grandpa);
							
					}
					else
					{
						if (node->parent == grandpa->left)
						{
							// std::cout << "here3 node key is :" << node->data.first << std::endl;
							if (node == node->parent->right)
							{
								// std::cout << "here4 node key is :" << node->data.first << std::endl;
								node = node->parent;
								leftRotate(node);
							}
							node->parent->color = BLACK;
							grandpa->color = RED;
							rightRotate(grandpa);
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								rightRotate(node);
							}
							node->parent->color = BLACK;
							grandpa->color = RED;
							leftRotate(grandpa);
						}
					}
				}
			}

			nodeptr findUncle(nodeptr node)
			{
				nodeptr grandpa = findGrandpa(node);
				if (grandpa)
				{
					if (node->parent == grandpa->left)
						return (grandpa->right);
					else
						return (grandpa->left);
				}
				return (nullptr_t);
			}
			
			nodeptr findGrandpa(nodeptr node)
			{
				if (node && node->parent)
					return (node->parent->parent);
				return (nullptr_t);
			}

			//Deletion helper function

			nodeptr rightNav(nodeptr node)
			{
				if (node == TNULL)
					return TNULL;
				while (node->right != TNULL)
					node = node->right;
				return node;
			}

			nodeptr leftNav(nodeptr node)
			{
				if (node == TNULL)
					return TNULL;
				while (node->left != TNULL)
					node = node->left;
				return node;
			}
			/**find the right most left subtree
			 1. check left of the node see if it is TNULL
			 2. if it exist, then move to the left node and keep moving right from there until the end
			 3. if it doesn't exist, check if the given node is left node of its parent
			 3.a if the condition fullfilled, move up one node and check for its condition again until the node isn't left node of its parent
			 	while updating predecessor being the parent node as it traverse
			 4. if all else failed, return nulltpr **/
			nodeptr	predecessor(nodeptr node)
			{
				nodeptr pred = NULL;
				if (node->left != TNULL)
				{
					pred = node->left;
					return (rightNav(pred));
				}
				pred = node->parent;
				for (;pred != TNULL && node == pred->left; node = pred)
					pred = pred->parent;
				return pred;
			}
			/**find the left most right subtree
			 1. check right of the node see if it is TNULL
			 2. if it exist, then move to the right node and keep moving left from there until the end
			 3. if it doesn't exist, check if the given node is right node of its parent
			 3.a if the condition fullfilled, move up one node and check for its condition again until the node isn't right node of its parent
			 	while updating successor being the parent node as it traverse
			 4. if all else failed, return nulltpr **/
			nodeptr	successor(nodeptr node)
			{
				nodeptr succ = nullptr_t;
				if (node->right != TNULL)
				{
					succ = node->right;
					return (leftNav(succ));
				}
				succ = node->parent;
				for (;succ != TNULL && node == succ->right; node = succ)
					succ = succ->parent;
				return succ;
			}

	
			/**Change parent of node to point to the target and target's parent to node->parent
			 eg A<->Node<->Target to A<->Target A<-Node->Target, doesn't update children*/
			void	nodeSwap(nodeptr node, nodeptr target)
			{
				if (node == this->root)
					root = target;
				else if (node == node->parent->left)
					node->parent->left = target;
				else 
					node->parent->right = target;
				target->parent = node->parent;
			}
			
			/**promote children of deletion node and link it to the target node if the deletion node have 2 children
			if target is not directly below deletion node, we swap its with right children
			let y = target->right, before swap p<->target<->y; after swap it became p<->y<->node(right)
			the reason right child is chosen because target is inorder successor, which is the left most right subtree, which means the only possible
			children it have would be on its right
			now that target node is free, we can swap it with node, from p1<->node<->child to p1<->target<->child, and deletion node is freed **/
			nodeptr	nodePromote(nodeptr node, nodeptr target)
			{
				nodeptr	temp = target->right;
				if (target->parent == node)
					temp->parent = target;
				else
				{
					nodeSwap(target, target->right);
					target->right = node->right;
					target->right->parent = target;
				}
				nodeSwap(node, target);
				target->left = node->left;
				target->left->parent = target;
				target->color = node->color;
				return temp;
			}
			
			/*for predecessor*/
			void	nodePromote2(nodeptr node, nodeptr target)
			{
				nodeptr temp = target->left;
				if (target->parent != node)
				{
					nodeSwap(target, temp);
					target->left = node->left;
					target->left->parent = target;
				}
				nodeSwap(node, target);
				target->right = node->right;
				target->right->parent = target;
				target->color = node->color;
			}

			size_type deletion(Key key)
			{
				nodeptr node = searchPair(key);
				if (node != TNULL)
				{
					initDelete(node);
					return 1;
				}
				return 0;
			}

			void initDelete(nodeptr node)
			{
				nodeptr	temp;
				bool	color = node->color;
				if (node == TNULL)
					return ;
				//case 1 if node only have one internal child
				if (node->left == TNULL)
				{	
					temp = node->right;
					nodeSwap(node, temp);
				}
				else if (node->right == TNULL)
				{
					temp = node->left;
					nodeSwap(node, temp);
				}
				else
				{
					nodeptr pred = successor(node);
					color = pred->color;
					temp =	nodePromote(node, pred);
				}
				// _alloc.destroy(node);
				_alloc.deallocate(node, 1);
				if (color == BLACK)
					deletionCorrection(temp);
				TNULL->left = leftNav(root);
				TNULL->right = rightNav(root);
			}
			/*Similar to insertcorrection, there is a left option and right option 
			 To make life easier, i use same algorithm but with opposite side for 4 different case for left and right
			 Case 1, if sibling is red
			 change sibling  to black and the parent to red then rotate it
			 since now sibling would become the parent and the parent would become its children, update the new sibling
			 since previously sibling is red, its left node which is the new sibling will always be black, hence we can pass it to the next case
			 
			 if the sibling is black
			 
			 case 2 if the sibling children is all black
			 change the colour of sibling to red and call the function again by passing in node->parent so that it will fulfill case 3
			 
			 case 3 if the sibling children is red
			 
			 case 3a if the red children isn't aligned with sibling and its parent, do a rotation to make it alligned
			 
			 rotation on the parent node so that sibling would be a new parent, and inherit parent node colour, both new children of sibling would be colored black */

			
			void	deletionCorrection(nodeptr node)
			{
				
				if (node != root && node->color == BLACK)
				{		
					nodeptr sibling;
					if (node == node->parent->left)
					{
						sibling = node->parent->right;
						//case 1
						if (sibling->color == RED)
						{
							sibling->color = BLACK;
							node->parent->color = RED;
							leftRotate(node->parent);
							sibling = node->parent->right;
						}
						//case 2
						if (sibling->color == BLACK)
						{
							if (sibling->left->color == BLACK && sibling->right->color == BLACK)
							{
								sibling->color = RED;
								deletionCorrection(node->parent);
							}
						//case 3
							else
							{
							//case 3a
								if (sibling->left->color == RED)
								{
									sibling->left->color = BLACK;
									sibling->color = RED;
									rightRotate(sibling);
									sibling = node->parent->right;
								}
								sibling->color = node->parent->color;
								node->parent->color = BLACK;
								sibling->right->color = BLACK;
								leftRotate(node->parent);
							}
						}
					}
					else
					{
						sibling = node->parent->left;
						//case 1
						if (sibling->color == RED)
						{
							sibling->color = BLACK;
							node->parent->color = RED;
							rightRotate(node->parent);
							sibling = node->parent->left;
						}
						//case 2
						if (sibling->color == BLACK)
						{
							if (sibling->left->color == BLACK && sibling->right->color == BLACK)
							{
								sibling->color = RED;
								deletionCorrection(node->parent);
							}
						//case 3
							else
							{
								//case 3a
								if (sibling->right->color == RED)
								{
									sibling->right->color = BLACK;
									sibling->color = RED;
									leftRotate(sibling);
									sibling = node->parent->left;
								}
								sibling->color = node->parent->color;
								node->parent->color = BLACK;
								sibling->left->color = BLACK;
								rightRotate(node->parent);
							}
						}
					}
				}
				node->color = BLACK;		
			}


		  // For balancing the tree after deletion
  
			// void	fullDelete(void)
			// {

			// 	nodeptr node = rightNav(root);
			// 	while (node != root)
			// 	{
			// 		nodeptr del = node;
			// 		node = predecessor(node);
			// 		// std::cout << del->data.first << std::endl;
			// 		// std::cout<< "black depth diff :" << blackDepthDiff(root) << std::endl;
			// 		initDelete(del);
			// 	}
			// 	node = leftNav(root);
			// 	while (node != root)
			// 	{
			// 		nodeptr del = node;
			// 		node = successor(node);
			// 		// std::cout << del->data->?<< std::endl;
			// 		// std::cout<< "black depth diff :" << blackDepthDiff(root) << std::endl;
			// 		initDelete(del);
			// 	}
			// 	// _alloc.deallocate(root, 1);
			// 	root = TNULL;
			// }

			void	fullDelete(void)
			{
				// if (root != TNULL)
				deleteRecursion(root);
				root = TNULL;
			}
			void	deleteSentinel(void)
			{
				_alloc.deallocate(TNULL, 1);
			}
			void deleteRecursion(nodeptr node)
			{
				if (node->left != TNULL)
				{
					deleteRecursion(node->left);
					return ;
				}
				if (node->right != TNULL)
				{
					deleteRecursion(node->right);
					return;
				}
				initDelete(node);
			}
			// nodeptr	findSibling(nodeptr node)
			// {
			// 	if (node && node->parent)
			// 	{
			// 		if (node == node->parent->left)
			// 			return node->parent->right;
			// 		else
			// 			return node->parent->left;
			// 	}
			// 	return nullptr_t;
			// }

			// int	blackDepth(nodeptr root)
			// {
			// 	if (!root)
			// 		return 0;
			// 	int	left = blackDepth(root->left);
			// 	int	right = blackDepth(root->right);
			// 	int cur = root->color ? 0 : 1;
			// 	return (cur + std::max(left, right));
			// }

			// int	blackDepthDiff(nodeptr root)
			// {
			// 	if (!root)
			// 		return (0);
			// 	int left = blackDepth(root->left);
			// 	int right = blackDepth(root->right);
			// 	return std::abs(left - right);
			// }

			size_type	size() const
			{
				return 1;
			}

			nodeptr searchPair(const Key& key) const
			{
				return searchIn(root, key);
			}

			// nodeptr searchKey(const key_type &a) const
			// {
			// 	return searchIn(root, a);
			// }
			nodeptr	searchIn(nodeptr root, const Key& v) const
			{
				if (root == TNULL || equal(v,root->data))
					return root;
				if (_com(v , root->data))
					return searchIn(root->left, v);
				else
					return searchIn(root->right, v);
			}
			bool	isEmpty(void)
			{
				if (root->right == nullptr_t)
					return (BLACK);
				return (RED);
			}
			void printTree() 
			{
			if (root) 
				printHelper(this->root, "", BLACK);
			}

			nodeptr	getRoot(void)
			{
				if (root)
					return (root);
				// return (nullptr_t);
			}

			nodeptr getValue(void) const
			{
				return TNULL;
			}

		
		// friend bool operator==(const ft::RedBlackTree<Key, T, Alloc>& lhs,
		// 			const ft::RedBlackTree<Key, T, Alloc>& rhs ) 
		// 			{
		// 	return ft::equal(ft:lhs, lhs.end(), rhs.begin());
		// };

        private:
			Allocator _alloc;
			Compare _com;
            nodeptr TNULL;
			nodeptr root;
		
    };

}

#endif
