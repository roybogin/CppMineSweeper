#pragma once
#include "Data.h"

class Panel	//a game panel
{

private:
	bool hasBomb;
	bool viewed;	//already viewed
	bool flagged;
	std::pair<int, int> gridPos;	//position in grid (between [0,0] and [ROWS-1, COLS-1])
	sf::Vector2f position;	//position on screen
	std::string text;
	sf::Vector2f size;
	sf::Color backColor;
	sf::Color foreColor;

public:
	Panel(std::pair<int, int> gridPos, sf::Vector2f location);	//create a panel
	void addBomb();	//add a bomb to the panel
	int bombsAround();	//get number of bombs on panels around
	int showSquare();	//show the number value of the panel
	void leftClick();
	void rightClick();
	
	//getters
	bool getHasBomb();
	bool getViewed();
	std::pair<int, int> getGridPos();
	sf::Vector2f getPosition();
	std::string getText();
	sf::Vector2f getSize();
	sf::Color getBackColor();
	sf::Color getForeColor();
private:
	std::vector<Panel*> getAround();	//get a list of the bombs around
};

