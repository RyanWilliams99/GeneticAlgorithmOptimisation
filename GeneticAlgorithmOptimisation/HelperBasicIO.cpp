#include "HelperBasicIO.h"

#include <iostream>
#include <string>


//Checking
bool IsNumber(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


//Input
int GetIntFromUser(uint16_t min, uint16_t max)
{
	std::string input;
	getline(std::cin, input);
	if (IsNumber(input))
		if (std::stoi(input) >= min && std::stoi(input) <= max)
			return std::stoi(input);
	PrintLines("Invalid input", 2);
}
std::string GetStringFromUser()
{
	std::string input;
	getline(std::cin, input);

	return input;
}

//Output
void Print(std::string str)
{
	std::cout << str;
}
void PrintLine(std::string str)
{
	std::cout << str << std::endl;
}
void PrintLines(std::string str, uint16_t numberOfLines)
{
	std::cout << str;
	for (size_t i = 0; i < numberOfLines; i++)
		std::cout << std::endl;
}
void PrintBinary(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (i % 4 == 0 && i != 0)
			std::cout << " ";
		std::cout << str[i];
	}
	PrintLine("");
}
