#pragma once
#include <SFML/Graphics.hpp>
#include "App.h"

class Player
	: public sf::Drawable
{
public:
	Player(App& app);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture& m_texture;
};