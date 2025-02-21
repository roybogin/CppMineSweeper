#include "Data.h"
#include "Funcs.h"



void createBoard()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			grid[row * COLS + col] = new Panel(std::pair<int, int>(row, col), Vector2f((LENGTH + MARGIN) * col + MARGIN, (LENGTH + MARGIN) * row + MARGIN));
		}
	}
}

void deleteBoard()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			delete grid[row * COLS + col];
		}
	}
}

void generateBombs(int number, Panel* panel)
{
	if (number >= ROWS * COLS)
		throw std::runtime_error("The number of the bombs is too high");	// maximum number of bombs is numbers of panels
	else
	{
		int i = 0;
		srand(time(0));	//randomize using current time
		while (i < number)
		{
			int randomRow = rand() % ROWS;
			int randomCol = rand() % COLS;
			Panel* p = grid[randomRow * COLS + randomCol];
			if (p->getHasBomb() || p == panel)
				continue;	//skip if p has a bomb
			p->addBomb();
			i++;
		}
	}
}

void victory()
{
	if (!lost)
	{
		endTime = std::chrono::system_clock::now();
		background = Color(0, 255, 127);
		won = true;
	}
}

void loss()
{
	if (!won)
	{
		background = Color(255, 0, 0);
		lost = true;
	}
}

Panel* getPanel(sf::Vector2f location)
{
	int endCol = (int)floor((location.x - MARGIN) / (LENGTH + MARGIN));	//column of click as if the margin is connected to a panel's end
	int startCol = (int)ceil((location.x - MARGIN - LENGTH) / (LENGTH + MARGIN));	//column of click as if the margin is connected to a panel's beginning
	if (endCol != startCol)	//only if the player clicked on margin
		return NULL;
	int endRow = (int)floor((location.y - MARGIN) / (LENGTH + MARGIN));
	int startRow = (int)ceil((location.y - MARGIN - LENGTH) / (LENGTH + MARGIN));
	if (endRow != startRow)
		return NULL;
	return grid[startRow * COLS + startCol];
}