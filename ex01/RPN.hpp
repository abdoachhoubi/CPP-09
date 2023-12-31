#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

class RPN
{
public:
	RPN();
	RPN(RPN const &other);
	RPN &operator=(RPN const &other);
	~RPN();
	void calcule(std::string line);
	float doOpeartion(float num1, float num2, char op);

private:
	std::stack<float> _stack;
};