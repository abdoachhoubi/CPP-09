#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	std::map<int, float> data;
	if (ac !=  2)
	{
		std::cout << "Error: couldn't open file " << std::endl;
		return 1;
	}
	parseCsvData (data);
	if (!data.size()) { 
		std::cout << "Error: data file is empty!" << std::endl;
		return 1;
		}
	parseDataFile(av[1], data);
} 
