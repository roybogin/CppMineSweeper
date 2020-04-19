#pragma once
#include <SFML/Graphics.hpp>
#include "Panel.h"
#include <chrono>
using namespace sf;

const int ROWS = 8;
const int COLS = 8;
const int BOMBS = 8;
const int LENGTH = 50;
const int MARGIN = 10;
const bool MLSolver = false;	//for machine learning
extern int unviewed;	//how many panels are unviewed
extern bool won;	//did the player win
extern bool lost;	//did the player lose
extern Color background;	//current background color
extern RenderWindow window;
const Color colors[8] = { sf::Color(1, 0, 254), sf::Color(1, 127, 1), sf::Color(254, 0, 0), sf::Color(1, 0, 125), sf::Color(128, 0, 0), sf::Color(0, 127, 126), sf::Color(0, 0, 0), sf::Color(128, 128, 128) };	//colors for numbers between 1 and 8

extern std::chrono::time_point<std::chrono::system_clock> startTime;
extern std::chrono::time_point<std::chrono::system_clock> endTime;
extern Panel* grid[ROWS * COLS];


