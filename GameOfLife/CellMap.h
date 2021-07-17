#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Cell.h"

class CellMap
{
public:
	CellMap(unsigned int gridSizeX, unsigned int gridSizeY);
	
	Cell* GetCell(unsigned int xPos, unsigned int yPos);

	void Update();
	void RefreshStates();
	void Reset();
	void Randomise();
	void InvertColours();
	void Draw(sf::RenderWindow& window);

private:
	unsigned int gridSizeX;
	unsigned int gridSizeY;
	std::vector<std::vector<Cell>> grid;
};
