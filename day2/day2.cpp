#include "adventofcode2023.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Game
{
    int id = 1;
    int red = 0;
    int green = 0;
    int blue = 0;
};

//day2 functions
std::string cutString(std::string s) //removes all but ints, colors, and spaces
{
    s.erase(0, s.find(':') + 2);
    std::replace(s.begin(), s.end(), ',', ' ');
    std::replace(s.begin(), s.end(), ';', ' ');
    return s;
}

bool isPossible(Game game, Game controlBag)
{
    return (!(game.red > controlBag.red || game.green > controlBag.green || game.blue > controlBag.blue));
}

Game createGame(std::string s) //returns Game with the max number of cubes pulled for each color
{
    static int idIterator = 1;
    Game currentGame = { idIterator, 0,0,0 };
    int cubesBuffer;
    std::string colorBuffer = "";
    std::stringstream ss;
    ss << s;

    while (!ss.eof()) {
        ss >> cubesBuffer >> colorBuffer;

        if (colorBuffer == "red")
        {
            if (cubesBuffer > currentGame.red)
            {
                currentGame.red = cubesBuffer;
            }
        }
        else if (colorBuffer == "green")
        {
            if (cubesBuffer > currentGame.green)
            {
                currentGame.green = cubesBuffer;
            }
        }
        else if (colorBuffer == "blue")
        {
            if (cubesBuffer > currentGame.blue)
            {
                currentGame.blue = cubesBuffer;
            }
        }
    }
    idIterator++;
    return currentGame;
}

void day2()
{
    //variables
    std::ifstream input("day2input.txt");
    std::string output;
    Game controlBag{0, 12, 13, 14};
    std::string cutOutput;
    Game bufferGame;
    int sum = 0;
    int sumOfPower = 0;

    while (getline(input, output))
    {
        cutOutput = cutString(output);
        bufferGame = createGame(cutOutput);
        if (isPossible(bufferGame, controlBag))
        {
            sum += bufferGame.id;
        }
        sumOfPower += (bufferGame.red * bufferGame.green * bufferGame.blue);
    }
    std::cout << "Part 1: " << sum << '\n';
    std::cout << "Part 2: " << sumOfPower << '\n';
}