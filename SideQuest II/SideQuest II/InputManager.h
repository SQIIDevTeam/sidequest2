#pragma once
#include <vector>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class InputManager
{
public:
	InputManager(sf::RenderWindow& w);
	~InputManager(void);
	void update();

	// Keyboard
	bool isKeyPressed(sf::Keyboard::Key key);
	bool isKeyHit(sf::Keyboard::Key key);

	// Maus
	sf::Vector2f getMousePos();
	bool isButtonPressed(sf::Mouse::Button button);
	bool isButtonHit(sf::Mouse::Button button);
	bool isSpritePressed(sf::Sprite& sprite, sf::Mouse::Button b);
	bool isSpriteHit(sf::Sprite& sprite, sf::Mouse::Button b);

private:
	std::map<sf::Keyboard::Key, bool> m_keys_pressed;
	std::map<sf::Keyboard::Key, bool> m_prev_keys_pressed;

	std::map<sf::Mouse::Button, bool> m_mouse_pressed;
	std::map<sf::Mouse::Button, bool> m_mouse_prev_pressed;

	sf::RenderWindow& m_window;
};