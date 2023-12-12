#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &filename) : filename(const_cast<std::string &>(filename)) {
	readInputFile(filename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : filename(other.filename) {
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		this->filename = other.filename;
		this->change_rate = other.change_rate;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::readInputFile(std::string file) {
	std::ifstream	ifs(file);
	std::string		line;

	if (!ifs.is_open())
		throw BitcoinExchange::InvalidFileException();
	while (std::getline(ifs, line)) {
		parseFile(line);
	}
	ifs.close();
}

void	BitcoinExchange::parseFile(std::string line) {
	std::string		date;
	std::string		rate;
	std::string		sep = ":";
	size_t			pos;

	pos = line.find(sep);
	if (pos == std::string::npos)
		throw BitcoinExchange::InvalidFileException();
	date = line.substr(0, pos);
	rate = line.substr(pos + 1);
	checkDates(date);
	change_rate[date] = std::stod(rate);
}

void	BitcoinExchange::checkDates(std::string line) {
	std::string		sep = "-";
	size_t			pos;
	std::string		year;
	std::string		month;
	std::string		day;

	pos = line.find(sep);
	if (pos == std::string::npos)
		throw BitcoinExchange::InvalidDateException();
	year = line.substr(0, pos);
	line = line.substr(pos + 1);
	pos = line.find(sep);
	if (pos == std::string::npos)
		throw BitcoinExchange::InvalidDateException();
	month = line.substr(0, pos);
	day = line.substr(pos + 1);
	if (year.size() != 4 || month.size() != 2 || day.size() != 2)
		throw BitcoinExchange::InvalidDateException();
}

void	BitcoinExchange::printHistoryChange() {
	std::map<std::string, double>::iterator	it;
	std::map<std::string, double>::iterator	it2;
	double									change;

	it = change_rate.begin();
	it2 = change_rate.begin();
	it2++;
	while (it2 != change_rate.end()) {
		change = (it2->second - it->second) / it->second * 100;
		std::cout << it->first << " -> " << it2->first << " : " << change << "%" << std::endl;
		it++;
		it2++;
	}
}

// Defining the exception classes
const char *BitcoinExchange::InvalidFileException::what() const throw() {
	return "Invalid file";
}

const char *BitcoinExchange::InvalidDateException::what() const throw() {
	return "Invalid date";
}

const char *BitcoinExchange::InvalidRateException::what() const throw() {
	return "Invalid rate";
}
