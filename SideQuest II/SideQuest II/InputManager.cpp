#include "InputManager.h"
#include <algorithm>

InputManager::InputManager(sf::RenderWindow& w)
	: m_window(w)
{
}


InputManager::~InputManager(void)
{
}

void InputManager::update()
{
	m_prev_keys_pressed = m_keys_pressed;
	m_keys_pressed.clear();

	for (sf::Keyboard::Key k = sf::Keyboard::A; k != sf::Keyboard::KeyCount; k = static_cast<sf::Keyboard::Key>(k + 1)) // Iterate through Keys. KeyCount is always the last enum entry
	{
		if (sf::Keyboard::isKeyPressed(k))
			m_keys_pressed[k] = true;
	}

	m_mouse_prev_pressed = m_mouse_pressed;
	m_mouse_pressed.clear();

	for (sf::Mouse::Button b = sf::Mouse::Left; b != sf::Mouse::ButtonCount; b = static_cast<sf::Mouse::Button>(b + 1))
	{
		if (sf::Mouse::isButtonPressed(b))
			m_mouse_pressed[b] = true;
	}
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key)
{
	return (m_keys_pressed.find(key) != m_keys_pressed.end());
}

bool InputManager::isKeyHit(sf::Keyboard::Key key)
{
	return ((m_prev_keys_pressed.find(key) == m_prev_keys_pressed.end()) && (m_keys_pressed.find(key) != m_keys_pressed.end()));
}

sf::Vector2f InputManager::getMousePos()
{
	return sf::Vector2f(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
}

bool InputManager::isButtonPressed(sf::Mouse::Button button)
{
	return (m_mouse_pressed.find(button) != m_mouse_pressed.end());
}

bool InputManager::isButtonHit(sf::Mouse::Button button)
{
	return ((m_mouse_prev_pressed.find(button) == m_mouse_prev_pressed.end()) && (m_mouse_pressed.find(button) != m_mouse_pressed.end()));
}

bool InputManager::isSpritePressed(sf::Sprite& sprite, sf::Mouse::Button b)
{
	return (isButtonPressed(b) && sprite.getGlobalBounds().contains(this->getMousePos()));
}

bool InputManager::isSpriteHit(sf::Sprite& sprite, sf::Mouse::Button b)
{
	return (isButtonHit(b) && sprite.getGlobalBounds().contains(this->getMousePos()));
}