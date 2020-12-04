#pragma once
#include <string>

/////////////////////////////////////////
//Generic helper functions for basic IO//
/////////////////////////////////////////

//Input
int GetIntFromUser(uint16_t min, uint16_t max);
std::string GetStringFromUser();

//Output
void Print(std::string str);
void PrintLine(std::string str);
void PrintLines(std::string str, uint16_t NumberOfLines);
void PrintBinary(std::string str);
