#pragma once
#pragma comment(lib,"ws2_32.lib")

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Panel.h"
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include "Socket.h"

using namespace sf;

const int ROWS = 4;
const int COLS = 4;
const int BOMBS = 3;
const int LENGTH = 100;	//pixel length of a tile
const int MARGIN = 20;	//space between tiles
const bool MLSolver = false;	//for machine learning
const bool SHOW_GAME = true;	//do you want to see the game while in ml
extern bool firstClick;
extern int unviewed;	//how many panels are unviewed
extern bool won;	//did the player win
extern bool lost;	//did the player lose
extern Color background;	//current background color
extern RenderWindow window;
//colors for each digit (1-8)
const Color colors[8] = { sf::Color(1, 0, 254), sf::Color(1, 127, 1), sf::Color(254, 0, 0), sf::Color(1, 0, 125), sf::Color(128, 0, 0), sf::Color(0, 127, 126), sf::Color(0, 0, 0), sf::Color(128, 128, 128) };	//colors for numbers between 1 and 8

//info for the socket
const PCSTR IP_ADDR = "127.0.0.1";
const PCSTR PORT = "2000";

extern std::chrono::time_point<std::chrono::system_clock> startTime;
extern std::chrono::time_point<std::chrono::system_clock> endTime;
extern Panel* grid[ROWS * COLS];	//array of panel pointers = the game board


