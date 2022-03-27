#include "Data.h"
#include "Funcs.h"
#include <chrono>
#include <thread>
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
bool firstClick;

void init()	//initiate the game
{	
	won = false;
	lost = false;
	firstClick = true;
	unviewed = ROWS * COLS;	//number of unviewed tiles

	if (!MLSolver || SHOW_GAME)
	{
		if (!(font.loadFromFile("C:\\Users\\roybo\\Desktop\\git repos\\CppMineSweeper\\arial.ttf")))	//load font for text
		{
			std::cout << "Error loading file" << std::endl;
			system("pause");
		}
		startTime = std::chrono::system_clock::now();
		background = Color(255, 255, 255);
	}

	createBoard();

	if (MLSolver)
	{
		socketCreate();
		socketConnect();
	}
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
	if (!MLSolver)
	{
		if (lost)	//show message if loss
		{
			MessageBox(NULL, "You hit a bomb", "AW", MB_OK);
			exit(0);
		}
		else if (won)	//if won show time it took
		{
			int seconds = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
			std::string message = "You Won\nTime it took: " + std::to_string(seconds / 60) + ":" + std::to_string(seconds % 60);
			MessageBox(NULL, message.c_str(), "WooHoo", MB_OK);
			exit(0);
		}

	}
	
}

void mlUpdate()
{
	while (1)
	{
		std::string done = "false";
		std::string didWin = "false";
		int reward = 0;
		std::string recieved = socketRecv();
		std::string toSend = "";
		if (recieved == "input_num" || recieved == "action_num")	//input num = number of NN inputs, action_num = number of possible actions
			toSend = std::to_string(ROWS * COLS);
		else if (recieved == "reset")	//reset the game
		{
			won = false;
			lost = false;
			firstClick = true;
			unviewed = ROWS * COLS;
			deleteBoard();
			createBoard();
			std::string observation;
			for (int i = 0; i < ROWS * COLS; i++)
			{
				observation = observation + "-5";
				if (i != ROWS * COLS - 1)
					observation = observation + ", ";
			}
			toSend = observation;
		}
		else if (recieved == "close")	//close the game
		{
			exit(0);
		}
		else if (recieved.substr(0, 4) == "step")	//NN preforms action - action is revealing a tile
		{
			int action = stoi(recieved.substr(5));
			Panel* p = grid[action];

			if (p->getViewed())
			{
				reward = -1;
			}
			else
			{
				if (firstClick)
				{
					generateBombs(BOMBS, p);
					firstClick = false;
				}
				p->leftClick();
				if (p->getHasBomb())	//if the player clicked a bomb he lost
					lost = true;
				else if (BOMBS == unviewed)	//if everythong is viewed but the bombs the player won
					won = true;
				if (lost)
				{
					reward = -10;
					done = "true";
				}
				else
				{
					reward = 1;
					if (won)
					{
						done = "true";
						didWin = "true";
					}
				}
			}
			std::string observation;
			for (int i = 0; i < ROWS * COLS; i++)
			{
				std::string text = grid[i]->getText();
				if (text == "")
					text = "0";
				if (text == "O")
					text = "-5";
				if (text == "X")
					text = "15";
				observation = observation + text;
				if (i != ROWS * COLS - 1)
					observation = observation + ", ";
			}
			toSend = observation + "#" + std::to_string(reward) + "#" + done + "#" + didWin;	//info sent to the NN code
		}
		
		socketSend(toSend.c_str());
		if (SHOW_GAME)
		{
			draw();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

void mouseClick()	//action preformed when the mouse is clicked
{
	auto translated_pos = window.mapPixelToCoords(Mouse::getPosition(window));	//click position relative to frame
	Panel* p = getPanel(translated_pos);
	if (p != NULL)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (firstClick)
			{
				generateBombs(BOMBS, p);	//generating bombs only after first mouse click
				firstClick = false;
			}
			p->leftClick();
			if (p->getHasBomb())	//if the player clicked a bomb he lost
				loss();
			else if (BOMBS == unviewed)	//if everythong is viewed but the bombs the player won
				victory();
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			p->rightClick();
		}
		if (Mouse::isButtonPressed(Mouse::Middle))
		{
			init();	//middle click resets the game
		}
	}
}

int main()
{

	init();
	if (!MLSolver)	//if the machine learning isn't on
	{
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
					if (event.type == sf::Event::MouseButtonPressed)
					{
						mouseClick();
					}
				}
			}
			draw();
		}
	} 
	else  	//Machine learning code	
	{
		mlUpdate();
	}
	
	return 0;
}
