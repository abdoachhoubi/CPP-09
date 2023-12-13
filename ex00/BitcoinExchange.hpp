#pragma once

#include <stack>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <cctype>

// Function to parse the data file and populate the provided map
void parseDataFile(std::string inputFile, std::map<int, float> data);

// Function to find and calculate values based on the provided key and value string
void findAndCalculate(std::map<int, float> data, int key, std::string val);

// Function to convert a key to a date string
std::string keyToDate(int key);

// Function to parse data from a CSV file and populate the provided map
void parseCsvData(std::map<int, float>& data);

// Function to check if a given line is a header line
bool isHeaderLine(std::string line);

// Function to check the date format and perform necessary actions
int checkDate(std::string& date, int key);
