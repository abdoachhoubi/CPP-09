#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &other) : _stack(other._stack) {}

RPN &RPN::operator=(RPN const &other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

float RPN::doOpeartion(float num1, float num2, char op)
{
	return (op == '+' ? num1 + num2 : op == '-' ? num1 - num2
								  : op == '*'	? num1 * num2
												: num1 / num2);
}

void RPN::calcule(std::string line)
{
	char token;

	for (size_t i = 0; i < line.length(); i++)
	{
		token = line[i];
		if (token == ' ')
			continue;
		if (isdigit(token))
		{
			_stack.push(token - '0');
		}
		else if ((token == '+' || token == '-' || token == '*' || token == '/') && _stack.size() >= 2)
		{
			float num1 = _stack.top();
			_stack.pop();
			float num2 = _stack.top();
			_stack.pop();
			_stack.push(doOpeartion(num2, num1, token));
		}
		else
		{
			std::cout << "Error" << std::endl;
			return;
		}
	}
	if (_stack.size() == 1)
		std::cout << _stack.top() << std::endl;
	else
		std::cout << "Error" << std::endl;
}