#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Cell
{
public:
	Cell(sf::Vector2f size, sf::Vector2f position);

	bool GetState() const { return state; }

	void Update(std::array<bool, 8> neighborCellsStates);
	void CheckForStateUpdate();
	void SwitchState();
	void SetStateAlive();
	void SetStateDead();
	void InvertColours();
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	sf::Vector2f positionInGrid;
	bool state; // true = alive, false = dead
	bool nextState; // it checks next state for all cells then updates them at once
};
