#include "ft_iterator.tpp"


int	main(void)
{
	int	lol[10] = {1,2,3,4,5,6,7,8,9,10};
	ft::random_access_iterator<int> it(lol);
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << *it << std::endl;
		++it;
	}

	for (int i = 0; i < 10; i++)
	{
		--it;
		std::cout << *it << std::endl;
	}

	std::cout <<"this is index number 2 : "<< it[2] << std::endl;
}	