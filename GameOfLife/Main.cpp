#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include "Cell.h"
#include "CellMap.h"

enum class GameState { Prep = 0, Play };

float GetAverageFramerate(std::vector<float> pastFramerates)
{
	float total = 0.0f;
	for (float framerate : pastFramerates)
		total += framerate;
	return total / 10.0f;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game of Life", sf::Style::Close | sf::Style::Resize | sf::Style::Fullscreen);

	sf::View gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));
	sf::View hud(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));
	gameView.setCenter(gameView.getSize() / 2.0f);
	hud.setCenter(hud.getSize() / 2.0f);

	CellMap map(192, 108);

	sf::Font font;
	font.loadFromFile("../res/RobotoMono-Regular.ttf");
	sf::Text framerateCounter;
	sf::Text generationCounter;
	framerateCounter.setFont(font);
	generationCounter.setFont(font);
	framerateCounter.setCharacterSize(24);
	generationCounter.setCharacterSize(24);
	framerateCounter.setPosition(sf::Vector2f(30.0f, 30.0f));
	generationCounter.setPosition(sf::Vector2f(30.0f, 60.0f));

	GameState gameState = GameState::Prep;

	// use timers to make single inputs easier
	sf::Clock invertColoursTimer;
	sf::Clock clearTimer;
	sf::Clock changeFramerateTimer;

	// fps counter stuff
	sf::Clock frameTimer;
	std::vector<float> pastFramerates(10, 0.0f);
	float framerate = 0.0f;
	float averageFramerate = 0.0f;
	float updateRate = 4.0f;
	unsigned int frameCount = 0;
	unsigned int framerateLimit = 20;
	window.setFramerateLimit(framerateLimit);

	unsigned long generation = 0;

	while (window.isOpen())
	{
		frameTimer.restart();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					window.close();
					break;
				}
			}
		}

		if (gameState == GameState::Prep)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				Cell* cellPtr = map.GetCell(mousePos.x / 10, mousePos.y / 10);
				if (cellPtr == nullptr) continue;
				cellPtr->SetStateAlive();
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				Cell* cellPtr = map.GetCell(mousePos.x / 10, mousePos.y / 10);
				if (cellPtr == nullptr) continue;
				cellPtr->SetStateDead();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				map.Randomise();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				gameState = GameState::Play;
		}

		else if (gameState == GameState::Play)
		{
			map.Update();
			map.RefreshStates();
			generation++;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			map.Reset();
			map.RefreshStates();
			generation = 0;
			gameState = GameState::Prep;
		}

		// input checks
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			gameState = GameState::Prep;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && invertColoursTimer.getElapsedTime().asSeconds() > 0.5f)
		{
			map.InvertColours();
			invertColoursTimer.restart();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) && changeFramerateTimer.getElapsedTime().asSeconds() > 0.3f)
		{
			if (framerateLimit < 240)
			{
				framerateLimit += framerateLimit < 100 ? 5 : 20;
				window.setFramerateLimit(framerateLimit);
				changeFramerateTimer.restart();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) && changeFramerateTimer.getElapsedTime().asSeconds() > 0.3f)
		{
			if (!(framerateLimit == 5))
			{
				framerateLimit -= framerateLimit < 100 ? 5 : 20;
				window.setFramerateLimit(framerateLimit);
				changeFramerateTimer.restart();
			}
		}

		framerate = 1.0f / frameTimer.getElapsedTime().asSeconds();
		framerate = framerate > framerateLimit ? framerateLimit : framerate;
		pastFramerates.erase(pastFramerates.begin());
		pastFramerates.push_back(framerate);
		averageFramerate = GetAverageFramerate(pastFramerates);

		framerateCounter.setString(std::to_string((int)averageFramerate) + " FPS");
		generationCounter.setString("Generation " + std::to_string(generation));
		
		window.setView(gameView);
		map.Draw(window);

		window.setView(hud);
		window.draw(framerateCounter);
		window.draw(generationCounter);
		
		window.display();
	}
}
