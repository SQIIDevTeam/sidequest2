#pragma once
#include <SFML\Graphics.hpp>
class Config;

class App
{
public:
	App(Config& c);

	void run();

	sf::RenderWindow& window();
	const sf::RenderWindow& window() const;
private:
	void update();
	void render();
private:
	sf::RenderWindow m_window;
};

