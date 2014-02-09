#pragma once
#include <SFML/Graphics.hpp>
#include "App.h"

class Player
	: public sf::Drawable
{
public:
	Player(App& app);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);
private:
	sf::Texture& m_texture;
	sf::Vector2f m_position;
};