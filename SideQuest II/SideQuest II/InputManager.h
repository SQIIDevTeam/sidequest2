#pragma once
#include <vector>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
	This class handles the input.
*/
class InputManager
{
public:
	/**
		Constructs the input manager with a reference to a window.
	*/
	InputManager(sf::RenderWindow& w);
	~InputManager(void);

	/**
		Updates the input manager. This needs to be called every update frame (not render frame)
	*/
	void update();

	// Keyboard

	/**
		Returns true if the specified key is being hold down
		@param[in] key The key which you want to check
	*/
	bool isKeyPressed(sf::Keyboard::Key key);

	/**
		Returns true if the specified key is hold down just this frame
		@param[in] key The key which you want to check
	*/
	bool isKeyHit(sf::Keyboard::Key key);

	// Maus

	/**
		Returns the mouse position in a sf::Vector2f
	*/
	sf::Vector2f getMousePos();

	/**
		Returns true if the specified mouse button is being hold down
		@param[in] button The button which you want to check
	*/
	bool isButtonPressed(sf::Mouse::Button button);

	/**
		Returns true if the specified mouse button is hold down only this frame
		@param[in] button The button which you want to check
	*/
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