#include "BitcoinExchange.hpp"

int checkDate(std::string& date, int key)
{
    std::string::iterator it = date.end() - 1;
	while (it != date.begin() && (*it == ' ' || *it == '\t'))
		date.erase(it--);
	it = date.begin();
	while (*it == ' ')
        date.erase(it++);
	if ((date.length() != 10 || date.compare(5,2, "12") > 0 || date.compare(8,2, "31") > 0 || date.compare(5,2, "00") <= 0 || date.compare(8,2, "00") <= 0))
	{
		if (key)
		{
			std::cout<< date << "Error: Wrong date format in data file!" << std::endl;
			exit(0) ;
		}
		else
		{
			if (date.length())
				std::cout << "Error: bad input => " << date << std::endl;
			return 0;
		}
	}
	return (1);
}

bool isHeaderLine(std::string line)
{
    int i;
	int n = line.length();
	if (n == 0)
		return false;
	for (i = 0; i < n; i++)
	{
		if (isdigit(line[i]))
			break;
	}
	return (n == i);
}

void parseCsvData(std::map<int, float>& data)
{
    char* rem;
	int first_line = 1;
	std::string line;
	std::string date;
	std::string value;
	std::ifstream data_file("data.csv");
	if (data_file.fail()) { std::cout << "Error: couldn't open file to get data, exiting.." << std::endl; exit(0) ;}

	while (getline(data_file, line))
	{
		if (first_line && isHeaderLine(line))
			first_line = 0;
		else
		{
			value = "";
			std::stringstream buff(line);
			getline(buff, date, ',');
			getline(buff, value, ',');

			if (checkDate(date, 1))
			{
				int mkey = 0;
				if (value.length())
				{
					double mval = strtod (value.c_str(), &rem);
					date.erase(std::remove(date.begin(), date.end(), '-'), date.end());
					std::stringstream key(date);
					key >> mkey;
					data[mkey] = mval;
				}
			}
		}
	}
}

std::string keyToDate(int key)
{
    std::ostringstream oss;
	oss << key;
	std::string ret = oss.str();
	ret.insert(4, "-");
	ret.insert(7, "-");
	return ret;
}

void findAndCalculate(std::map<int, float> data, int key, std::string val)
{
    std::string date;
	char* rem;
	date = keyToDate(key);
	if (!val.length())
	{
		std::cout << "Error: value should be submitted." << std::endl;
		return;
	}
	double value = strtod (val.c_str(), &rem);
	if (rem[0] != '\0' )
		std::cout << "Error: bad format." << std::endl;
	else if (value < 0)
		std::cout << "Error: value not a positive number." << std::endl;
	else if ( value > 1000)
		std::cout << "Error: value too large. " << std::endl;
	else
	{
		std::map<int, float>::iterator it = data.begin();
		if (it->first > key)
		{
			std::cout << "Error: no data found "<< std::endl;
			return;
		}
		it = data.upper_bound(key);
			--it;
		if (it != data.end())
			std::cout << date <<" => " << value <<" = "<< it->second *  value << std::endl;
	}
}

void cleanValue(std::string& value)
{
    std::string::iterator it = value.begin();
	while (*it == ' ')
		value.erase(it++);
	while (it != value.end() )
	{
		if (*it == ',')
			value.replace(it, it+1, ".");
		++it;
	}
}

void parseDataFile(std::string inputFile, std::map<int, float> data)
{
    std::string line;
	std::string date;
	std::string val;
	std::ifstream file(inputFile);
	int first_line = 1;
	if (file.fail()) { std::cout << "Error: couldn't open file to get values, exiting.." << std::endl; exit(0) ;}
	while (getline(file, line) )
	{
		if (first_line && isHeaderLine(line))
			first_line = 0;
		else
		{
			std::stringstream redir(line);
			getline(redir, date, '|');
			getline(redir, val, '|');
			cleanValue(val);
			if (checkDate(date, 0) )
			{
				int mkey;
				date.erase(std::remove(date.begin(), date.end(), '-'), date.end());
				std::stringstream key(date);
				key >> mkey;
				findAndCalculate(data, mkey, val);
			}
		}
	}
}
