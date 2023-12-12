#include "adventofcode2023.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//day1 functions
std::string removeChars(std::string string)
{
    std::string newString = "";
    for (char c : string)
    {
        if (c >= 48 && c <= 57)
        {
            newString += c;
        }
    }
    return newString;
}

int numeralCharToInt(char c)
{
    return (c - 48);
}

void day1()
{
    //variables
    std::ifstream input("day1input.txt");
    std::string output;
    int firstDigit;
    int lastDigit;
    int sum = 0;

    while (getline(input, output))
    {
        output = removeChars(output);
        if (output.length() > 0) //required to protect against lines with no numerals
        {
            firstDigit = numeralCharToInt(output.front());
            lastDigit = numeralCharToInt(output.back());
        }
        else
        {
            firstDigit = 0;
            lastDigit = 0;
        }
        sum += (firstDigit * 10) + lastDigit;
    }
    std::cout << sum;
}

//day1part2 functions
std::string wordsToInts(std::string string)
{
    const std::vector<std::string> digits = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    for (int i = 0; i < digits.size(); i++)
    {
        while (string.find(digits[i]) != -1)
        {
            string.insert(string.find(digits[i]) + 1, std::to_string(i + 1));
        }
    }

    return string;
}

void day1part2()
{
    std::ifstream input("day1input.txt");
    std::string output;
    int firstDigit;
    int lastDigit;
    int sum = 0;

    while (getline(input, output))
    {
        output = wordsToInts(output); //add in ints with numeral words
        output = removeChars(output); //remove all non-ints

        if (output.length() > 0) //required to protect against lines with no numerals
        {
            firstDigit = numeralCharToInt(output.front());
            lastDigit = numeralCharToInt(output.back());
        }
        else
        {
            firstDigit = 0;
            lastDigit = 0;
        }
        sum += (firstDigit * 10) + lastDigit;
    }
    std::cout << sum;
}