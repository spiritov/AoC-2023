#include "adventofcode2023.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

//day 3 functions
void print(std::vector<std::string> vs)
{
	for (std::string s : vs)
	{
		std::cout << s << '\n';
	}
}

bool isSymbol(char c)
{
	return ((c < '0' || c > '9') && c != '.');
}

bool checkAdjacentSide(int position, std::string s) 
{
	return (isSymbol(s[position - 1]) || isSymbol(s[position + 1]));
}

bool checkAdjacentOther(int position, std::string s) 
{
	return (isSymbol(s[position - 1]) || isSymbol(s[position]) || isSymbol(s[position + 1]));
}

int partsSum(const std::string& string, const std::string& above, const std::string& below)
{
	int sum{ 0 };
	std::string tempInt{""};
	bool hasAdjacentSymbol{ false };
	for (int i = 1; i < string.length(); i++) //okay to check last char because it will always be '.'

	{
		if (std::isdigit(string[i]))
		{
			tempInt += string[i];
			
			if (!hasAdjacentSymbol) //check current string
			{
				hasAdjacentSymbol = checkAdjacentSide(i, string);
			}
			if (!hasAdjacentSymbol) //check string above
			{
				hasAdjacentSymbol = checkAdjacentOther(i, above);
			}
			if (!hasAdjacentSymbol) //check string below
			{
				hasAdjacentSymbol = checkAdjacentOther(i, below);
			}
		}
		else { //not on a digit
			if (hasAdjacentSymbol && tempInt.length() > 0 ) //add last adjacentSymbol number to the current string's sum
			{
				sum += stoi(tempInt);
				std::cout << tempInt << " is a part number." << '\n';
				hasAdjacentSymbol = false;
			}
			tempInt.clear();
		}
	}
	return sum;
}

std::string createBorderString(std::string s)
{
	std::string returnString {""};
	for (char c : s)
	{
		returnString += '.';
	}
	return returnString;
}

void day3()
{
	std::ifstream input("day3input.txt");
	std::string output;
	std::vector<std::string> fullInput{};
	std::string borderString{""};
	int cumulativeSum{ 0 };

	while (getline(input, output)) //create vector holding puzzle input
	{
		//so the entire "real" string can check all adjacent characters without going out of bounds
		output.insert(output.begin(), '.');
		output.push_back('.');

		fullInput.push_back(output);
	}
	//border strings don't need to be checked for valid part numbers
	borderString = createBorderString(fullInput[0]);
	fullInput.insert(fullInput.begin(), borderString);
	fullInput.push_back(borderString);

	for (int i = 1; i < fullInput.size()-1; i++) //iterate checking puzzle input strings only
	{
		cumulativeSum += partsSum(fullInput[i], fullInput[i-1], fullInput[i+1]);
	}
	std::cout << cumulativeSum;
}