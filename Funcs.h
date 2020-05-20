#pragma once
#include "Panel.h"
void createBoard();	//create the board and all of the panels
void deleteBoard();	//delete the panels to free up space
void generateBombs(int number, Panel* panel);	// generate the number of bombs in random panels
void victory();	//function if player won
void loss();	//function if player lost
Panel* getPanel(sf::Vector2f position);	//get panel in the said position (recognize which panel is clicked)

