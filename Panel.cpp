#include "Data.h"


Panel::Panel(pair<int, int> gridPos, sf::Vector2f location)
{
	this->gridPos = gridPos;
	this->position = location;
	text = "O";	//unchecked panel
	size = sf::Vector2f(LENGTH, LENGTH);
	backColor = Color(180, 180, 180);
	foreColor = Color(0, 0, 0);
	hasBomb = false;
	viewed = false;
	flagged = false;
}

vector<Panel*> Panel::getAround()
{
	vector<Panel*> lst;
	int row = gridPos.first;
	int col = gridPos.second;
	if (row != 0)	//if not on first row (there is a row above)
	{
		if (col != 0)
		{
			lst.push_back((grid[(row-1) * COLS + col - 1]));
		}

		lst.push_back((grid[(row-1) * COLS + col]));

		if (col != COLS-1)
		{
			lst.push_back((grid[(row - 1) * COLS + (col + 1)]));
		}
	}

	if (col != 0)
	{
		lst.push_back((grid[(row) * COLS + col - 1]));
	}

	lst.push_back((grid[(row) * COLS + col]));

	if (col != COLS - 1)
	{
		lst.push_back((grid[(row) * COLS + (col + 1)]));
	}

	if (row != ROWS - 1)	//if not on last row (there is a row below)
	{
		if (col != 0)
		{
			lst.push_back(grid[(row + 1) * COLS + col - 1]);
		}

		lst.push_back(grid[(row + 1) * COLS + col]);

		if (col != COLS - 1)
		{
			lst.push_back(grid[(row + 1) * COLS + (col + 1)]);
		}
	}
	return lst;
}

bool Panel::getHasBomb()
{
	return hasBomb;
}

bool Panel::getViewed()
{
	return viewed;
}

pair<int, int> Panel::getGridPos()
{
	return gridPos;
}
sf::Vector2f Panel::getPosition()
{
	return position;
}
string Panel::getText()
{
	return text;
}
sf::Vector2f Panel::getSize()
{
	return size;
}
sf::Color Panel::getBackColor()
{
	return backColor;
}
sf::Color Panel::getForeColor()
{
	return foreColor;
}

void Panel::addBomb()
{
	if (!hasBomb)
		hasBomb = true;
}

int Panel::bombsAround()
{
	int bombCount = 0;
	vector<Panel*> lst = getAround();
	for (Panel* p : lst)
	{
		if (p->getHasBomb())
		{
			bombCount++;
		}
	}
	return bombCount;
}

int Panel::showSquare()
{
	int bombCount = bombsAround();
	viewed = true;
	if (bombCount != 0)
	{
		text = to_string(bombCount);
		foreColor = colors[bombCount - 1];
		unviewed--;
		return 1;
	}
	else
	{	//if there are no bombs show numbers around (if not flagged)
		text = "";
		int shownCount = 1;
		unviewed--;
		vector<Panel*> lst = getAround();
		for(Panel* p : lst)
		{
			if ((!p->viewed) && (!p->flagged))
				shownCount += p->showSquare();	//recursion for the panels around the given one
		}
		return shownCount;
	}

}

int Panel::leftClick()
{
	if (!viewed && !flagged)
	{
		viewed = true;
		if (hasBomb)
		{
			text = "X";
			foreColor = Color(255, 0, 0);
			return 1;
		}
		else
		{
			return showSquare();
		}
	}
}

void Panel::rightClick()	//toggle flag
{
	if (!viewed)
	{
		if (flagged)
		{
			flagged = false;
			foreColor = Color(0, 0, 0);
			text = "O";
		}
		else
		{
			flagged = true;
			foreColor = Color(255, 0, 0);
			text = "F";
		}
	}
}