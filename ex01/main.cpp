#include "RPN.hpp"

int main(int ac, char **av)
{
	int tmp = 0;
	std::stack<int> my_stack;
	parseRPN(ac, av);
	for (int i = 0; av[1][i]; i++)
	{
		if (isdigit(av[1][i]) && isdigit(av[1][i+1]))
		{
			std::cout << "Error: only numbers  less than 10 are allowed!" << std::endl;
			exit (0);
		}
		if(isdigit(av[1][i]))
			my_stack.push(av[1][i] - '0');
		else if (av[1][i] == '/' || av[1][i] == '*' || av[1][i] == '-' || av[1][i] == '+' )
		{
			if (my_stack.size() < 2 )
			{
				std::cout << "Error: bad format!" << std::endl;
				exit (0);
			}
			tmp = my_stack.top();
			my_stack.pop();
			if (av[1][i] == '/')
			{
				if (tmp == 0)
				{
					std::cout << "Error: division on 0." << std::endl;
					exit(0);
				}
				tmp = my_stack.top() / tmp ;
			}
			if (av[1][i] == '*')
				tmp = my_stack.top() * tmp ;
			if (av[1][i] == '-')
				tmp = my_stack.top() - tmp ;
			if (av[1][i] == '+')
				tmp = my_stack.top() + tmp ;
			my_stack.pop();
			my_stack.push(tmp);
		}
	}
	if (my_stack.size() != 1)
		std::cout << "Error: invalid expression!" << std::endl;
	else
		std::cout << my_stack.top() << std::endl;
}
