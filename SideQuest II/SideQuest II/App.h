#pragma once
#include <SFML\Graphics.hpp>
#include "StateManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
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
	TextureManager texturemanager;
	FontManager fontmanager;
	InputManager inputmanager;
private:
	void update();
	void render();
private:
	float m_accumulator;
	sf::Clock m_clock;
};

