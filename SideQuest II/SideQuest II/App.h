#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Config.h"

class App
{
public:
	App(Config& c);

	void run();
	bool isFullscreen() const;
public:
	float timestep;
	sf::RenderWindow window;
	StateManager statemanager;
	TextureManager texturemanager;
	FontManager fontmanager;
	InputManager inputmanager;
	Config& config;
private:
	void update();
	void render();
	void onResize();
	void setFullscreen(bool fullscreen);
	void validateVideoMode(sf::VideoMode& mode);
private:
	float m_accumulator;
	sf::Clock m_clock;
	bool m_fullscreen;
	
};

