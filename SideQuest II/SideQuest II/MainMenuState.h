#pragma once
#include "State.h"
#include "Menu.h"

class MainMenuState :
	public State
{
public:
	MainMenuState(App& app);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();

	virtual void handleEvent(sf::Event& event);

private:
	sf::Texture& m_borderTexture;

	Menu m_menu;
};

