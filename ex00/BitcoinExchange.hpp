#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BitcoinExchange {
	public:
		// Contructors & Destructor (Canonical form)
		BitcoinExchange(const std::string &filename);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		class	InvalidFileException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class	InvalidDateException : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class	InvalidRateException : public std::exception {
			public:
				virtual const char *what() const throw();
		};
	
	private:
		std::string						&filename;
		std::map<std::string, double>	change_rate;

		void	readInputFile(std::string file);
		void	parseFile(std::string file);
		void	checkDates(std::string line);
		void	printHistoryChange();
};