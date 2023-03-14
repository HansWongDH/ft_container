#ifndef UTILITIES_HPP
#define UTILITIES_HPP


#include "iterator.hpp"


enum colour{
	BLACK,
	RED
};

/**
 * @brief self declared nulltpr_t since it doesn't exist in c++98;
 * 
 * 
 */
const class nullptr_t
{
	public:
   		template<class T>          /* convertible to any type       */
   		operator T*() const        /* of null non-member            */
      	{ return 0; }           /* pointer...                    */

   		template<class C, class T> /* or any type of null           */
      	operator T C::*() const /* member pointer...             */
      	{ return 0; }   

	private:
   		void operator&() const;    /* Can't take address of nullptr */

	} nullptr_t = {};               /* and whose name is nullptr     */

namespace ft
{
	template<bool, class T>    //i give it two parameters, up to you to give more or less
	struct enable_if
	{};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;     //if true define the T type value
	};

	//default template of is_integral;
	template<class T>
	struct is_integral{
		static const bool value = false;
	};

	//if T is the type bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long = true
	template<>
	struct is_integral<bool>{
		static const bool value = true;
	};

	template<>
	struct is_integral<char>{
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned int>{
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned char>{
		static const bool value = true;
	};
	template<>
	struct is_integral<signed char>{
		static const bool value = true;
	};

		template<>
	struct is_integral<short>{
		static const bool value = true;
	};

	template<>
	struct is_integral<int>{
		static const bool value = true;
	};

	template<>
	struct is_integral<long>{
		static const bool value = true;
	};

	template<>
	struct is_integral<long long>{
		static const bool value = true;
	};

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
 
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
	{
        if (!(*first1 == *first2))
            return false;
	}
    return true;
}

template<class inputIt>
typename std::iterator_traits<inputIt>::difference_type distance(inputIt first, inputIt last) {
    typename std::iterator_traits<inputIt>::difference_type result = 0;
    while (first != last) {
        ++first;
        ++result;
    }
    return result;
}

	template< class T>    
	struct remove_const
	{
		typedef T type;
	};
	

	// template <class T>
	// struct remove_const<true, T>
	// {
	// 	typedef const T type;    
	// };

	template <class T>
	struct remove_const<const T>
	{
		typedef T type;    
	};

	// template <class T>
	// struct remove_const<T>
	// {
	// 	typedef T type;    
	// };
	template<typename T>
	struct is_const {
   		static const bool value = false;
	};

	template<typename T>
	struct is_const<const T> {
    	static const bool value = true;
	};


	 template
    <typename T1,typename T2> 
    struct pair{
        pair() : first(), second()
        {
        };
        pair(const T1 &first, const T2 &second) : first(first), second(second) {};
		template<typename C1, typename C2>
		pair(const pair<C1, C2>& a) : first(a.first), second(a.second)
		{
		}
		// pair(const pair& a) : first(a.first), second(a.second)
		// {
		// }
		// pair&	operator=(const pair& a)
		// {
		// 	this->first = a.first;
		// 	this->second = a.second;
		// 	return *this;
		// }
		
        ~pair() {};
    
	
        T1  first;
        T2  second;

    };

	template
	<typename T1, typename T2>
	ft::pair<T1, T2> make_pair(T1 first, T2 second)
	{

		return ft::pair<T1, T2>(first, second);
	};

		template<typename T1, typename T2>
	bool operator==( const ft::pair<T1, T2>& lhs,
					const ft::pair<T1, T2>& rhs ) {
			return (lhs.first == rhs.first && lhs.second == rhs.second );
		};

	template< typename T1, typename T2 >
	bool operator!=( const ft::pair<T1, T2>& lhs,
					const ft::pair<T1, T2>& rhs ) {
			return !(lhs == rhs);		
		};


	template<typename T1, typename T2>
	bool operator<( const ft::pair<T1, T2>& lhs,
					const ft::pair<T1, T2>& rhs ) {
			 return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
		};

	template<typename T1, typename T2>
	bool operator<=( const ft::pair<T1, T2>& lhs,
					const ft::pair<T1, T2>& rhs ) {
			return !(rhs < lhs);
		};

	template<typename T1, typename T2>
	bool operator>( const ft::pair<T1, T2>& lhs,
					const ft::pair<T1, T2>& rhs ) {
			return rhs < lhs;
		};

	template<typename T1, typename T2>
	bool operator>=( const ft::pair<T1, T2>& lhs,
					const ft::pair<T1, T2>& rhs ) {
			return !(lhs < rhs);
		};

	template
    <typename T>
   	struct Node {
        T 		data;
        Node*   parent;
        Node*   left;
        Node*   right;
        bool	color;

	
		Node() : data()
		{
			parent = nullptr_t;
			left = nullptr_t;
			right = nullptr_t;
			color = BLACK;
		};

		Node(const T& key, Node* parent = nullptr_t, Node* left = nullptr_t, Node* right = nullptr_t) : data(key), parent(parent), left(left), right(right)
		{
		
			color = BLACK;
		}

		~Node() {}

		T	getData()
		{
			return this->data;
		}

		// Node* rightNav(Node* node, Node* sentinel)
		// {
		// 	if (!node)
		// 		return sentinel;
		// 	while (node->right != sentinel)
		// 		node = node->right;
		// 	return node;
		// }

		// Node* leftNav(Node* node, Node* sentinel)
		// {
		// 	if (!node)
		// 		return sentinel;
		// 	while (node->left != sentinel)
		// 		node = node->left;
		// 	return node;
		// }

		Node	&operator*()
		{
			return *this;
		}
		
		
    };

	template<typename T>
	struct my_less {
		bool operator()(const T& a, const T& b) const {
			return a < b;
		}
	};

	template<typename T1, typename T2>
	struct my_less<ft::pair<T1, T2> > {
		bool operator()(const ft::pair<T1, T2>& a, const ft::pair<T1, T2>& b) const {
			return a.first < b.first;
		}
	};



} // namespace ft


#endif
