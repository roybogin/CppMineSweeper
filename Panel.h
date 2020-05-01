#pragma once
#include "Data.h"
using namespace std;


class Panel	//a game panel
{

private:
	bool hasBomb;
	bool viewed;	//already viewed
	bool flagged;
	pair<int, int> gridPos;	//position in grid (between [0,0] and [ROWS-1, COLS-1])
	sf::Vector2f position;	//position on screen
	string text;
	sf::Vector2f size;
	sf::Color backColor;
	sf::Color foreColor;

public:
	Panel(pair<int, int> gridPos, sf::Vector2f location);	//create a panel
	void addBomb();	//add a bomb to the panel
	int bombsAround();	//get number of bombs on panels around
	void showSquare();	//show the number value of the panel
	void leftClick();
	void rightClick();
	
	//getters
	bool getHasBomb();
	bool getViewed();
	pair<int, int> getGridPos();
	sf::Vector2f getPosition();
	string getText();
	sf::Vector2f getSize();
	sf::Color getBackColor();
	sf::Color getForeColor();
private:
	vector<Panel*> getAround();	//get a list of the bombs around
};

