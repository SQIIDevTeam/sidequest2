#pragma once
#include "State.h"
class MainMenuState :
	public State
{
public:
	MainMenuState(App& app);
	~MainMenuState();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();
private:
	sf::Texture& m_borderTexture;
	sf::Sprite m_borderSprite;
};

