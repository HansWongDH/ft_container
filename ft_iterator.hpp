#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

namespace	ft
{
	class iterator
	{
	private:
		/* data */
	public:
		iterator();
		~iterator();
		iterator(const iterator &a);
		iterator&	operator=(const iterator &a);
		iterator&	operator==(const iterator &a);
		iterator&	operator!=(const iterator &a);
		iterator&	operator*(const iterator &a);
		iterator&	operator++(void);
		iterator&	operator++(int);
		iterator&	operator--(void);
		iterator&	operator--(int);
		iterator&	operator+(int);
		iterator&	operator+(const iterator &a);
		iterator&	operator-(int);
		iterator&	operator-(const iterator &a);
		iterator&	operator>(const iterator &a);
		iterator&	operator<(const iterator &a);
		iterator&	operator>=(const iterator &a);
		iterator&	operator<=(const iterator &a);
		iterator&	operator+=(const iterator &a);
		iterator&	operator-=(const iterator &a);
		iterator&	operator[](int);
	};
};

#endif