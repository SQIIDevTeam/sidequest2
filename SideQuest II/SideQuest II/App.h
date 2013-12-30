#pragma once

#include <SFML\Graphics.hpp>
#include "StateManager.h"
class Config;

class App
{
public:
	App(Config& c);

	void run();

public:
	float timestep;
	sf::RenderWindow window;
	StateManager statemanager;
private:
	void update();
	void render();
private:
	float m_accumulator;
	sf::Clock m_clock;
};

