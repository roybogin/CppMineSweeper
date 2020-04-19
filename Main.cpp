#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Data.h"
#include "Panel.h"
#include "Funcs.h"
using namespace sf;

RenderWindow window(VideoMode((LENGTH + MARGIN)* COLS + MARGIN, (LENGTH + MARGIN)* ROWS + MARGIN), "MineSweeper");
Panel* grid[ROWS * COLS];
Font font;
int unviewed;
std::chrono::time_point<std::chrono::system_clock> startTime;
std::chrono::time_point<std::chrono::system_clock> endTime;
Color background;
bool won;
bool lost;

void init()	//initiate the game
{
	won = false;
	lost = false;
	if (!(font.loadFromFile("arial.ttf")))
	{
		cout << "Error loading file" << endl;
		system("pause");
	}
	unviewed = ROWS * COLS;
	startTime = std::chrono::system_clock::now();
	background = Color(255, 255, 255);

	createBoard();
	generateBombs(BOMBS);
}


void draw()	//draw the panels and text
{
	window.clear(background);
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			RectangleShape shape((grid[row * COLS + (col)])->getSize());
			shape.setFillColor((grid[row * COLS + (col)])->getBackColor());
			shape.setPosition((grid[row * COLS + (col)])->getPosition());

			Text text(String(grid[row * COLS + col]->getText()), font);
			text.setPosition((grid[row * COLS + (col)])->getPosition() + Vector2f(LENGTH/4, LENGTH/4));
			text.setFillColor(grid[row * COLS + col]->getForeColor());
			text.setCharacterSize(LENGTH/2);
			
			window.draw(shape);
			window.draw(text);
		}

	}
	window.display();
	if (won)	//if won show time it took
	{
		int seconds = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
		string message = "You Won\nTime it took: " + to_string(seconds / 60) + ":" + to_string(seconds % 60);
		MessageBox(NULL, message.c_str(), "WooHoo", MB_OK);
	}
	else if (lost)	//show message if loss
	{
		MessageBox(NULL, "You hit a bomb", "AW", MB_OK);
	}
}

int main()
{
	init();
	draw();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (!won && !lost)	//while the player is still playing
			{
				if (!MLSolver)	//if the machine learning isn't on
				{
					if (event.type == sf::Event::MouseButtonPressed)
					{
						auto translated_pos = window.mapPixelToCoords(Mouse::getPosition(window));	//click position relative to frame
						Panel* p = getPanel(translated_pos);
						if (p != NULL)
						{
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								p->leftClick();
								if (BOMBS == unviewed)	//if everythong is viewed but the bombs the player won
									victory();
								if (p->getHasBomb())	//if the player clicked a bomb he lost
									loss();
							}
							if (Mouse::isButtonPressed(Mouse::Right))
							{
								p->rightClick();
							}
						}
					}
				}
				else  	//Machine learning code	
				{

				}
				draw();
			}
		}
	} 
	return 0;
}
