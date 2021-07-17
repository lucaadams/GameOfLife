#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include "CellMap.h"

CellMap::CellMap(unsigned int gridSizeX, unsigned int gridSizeY)
	: gridSizeX(gridSizeX), gridSizeY(gridSizeY)
{
	grid.reserve(gridSizeX);
	for (int x = 0; x < gridSizeX; x++)
	{
		std::vector<Cell> column;
		column.reserve(gridSizeY);
		for (int y = 0; y < gridSizeY; y++)
		{
			column.emplace_back(sf::Vector2f(10, 10), sf::Vector2f(x, y));
		}
		grid.push_back(column);
	}
}

Cell* CellMap::GetCell(unsigned int xPos, unsigned int yPos)
{
	if (xPos > gridSizeX || yPos > gridSizeY || xPos < 0 || yPos < 0)
		return nullptr;
	return &(grid[xPos][yPos]);
}

void CellMap::Update()
{
	// iterate through all cells in map and update them
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			// get neighbor cell states
			std::array<bool, 8> neighborCellStates;
			int i = 0;
			for (int x1 = x - 1; x1 < x + 2; x1++)
			{
				for (int y1 = y - 1; y1 < y + 2; y1++)
				{
					if (x1 == x && y1 == y)
					{
						continue;
					}
					neighborCellStates[i++] = (x1 < 0 || y1 < 0) || (x1 > gridSizeX - 1 || y1 > gridSizeY - 1) ?
						false : grid[x1][y1].GetState();
				}
			}
			grid[x][y].Update(neighborCellStates);
		}
	}
}

void CellMap::RefreshStates()
{
	// iterate through all cells in map and update them
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			grid[x][y].CheckForStateUpdate();
		}
	}
}

void CellMap::Randomise()
{
	srand((unsigned)time(0));
	float randomNum;
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			randomNum = rand() % 10;
			if (randomNum > 7)
				grid[x][y].SetStateAlive();
			else
				grid[x][y].SetStateDead();
		}
	}
}

void CellMap::Reset()
{
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			grid[x][y].SetStateDead();
		}
	}
}

void CellMap::InvertColours()
{
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			grid[x][y].InvertColours();
		}
	}
}

void CellMap::Draw(sf::RenderWindow& window)
{
	for (int x = 0; x < gridSizeX; x++)
	{
		for (int y = 0; y < gridSizeY; y++)
		{
			grid[x][y].Draw(window);
		}
	}
}
