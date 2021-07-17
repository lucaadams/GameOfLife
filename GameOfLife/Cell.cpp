#include <SFML/Graphics.hpp>
#include <array>
#include "Cell.h"

Cell::Cell(sf::Vector2f size, sf::Vector2f positionInGrid)
	: positionInGrid(positionInGrid), state(false), nextState(false)
{
	body.setSize(size);
	body.setPosition(positionInGrid * 10.0f);
	body.setFillColor(sf::Color::Black);
	body.setOutlineColor(sf::Color::White);
}

void Cell::Update(std::array<bool, 8> neighborCellsStates)
{
	unsigned int neighborsAlive = 0;
	for (bool state : neighborCellsStates)
	{
		if (state) // if alive
			neighborsAlive++;
	}

	if (state && (neighborsAlive < 2 || neighborsAlive > 3))
		nextState = false;
	else if (!state && neighborsAlive == 3)
		nextState = true;
}

void Cell::CheckForStateUpdate()
{
	if (nextState != state)
		SwitchState();
}

void Cell::SwitchState()
{
	state = state ? false : true;
	nextState = state;
	InvertColours();
}

void Cell::SetStateAlive()
{
	if (state)
		return;
	state = true;
	nextState = true;
	InvertColours();
}

void Cell::SetStateDead()
{
	if (!state)
		return;
	state = false;
	nextState = false;
	InvertColours();
}

void Cell::InvertColours()
{
	body.setFillColor(body.getFillColor() == sf::Color::Black ? sf::Color::White : sf::Color::Black);
	body.setOutlineColor(body.getFillColor() == sf::Color::Black ? sf::Color::White : sf::Color::Black);
}

void Cell::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
