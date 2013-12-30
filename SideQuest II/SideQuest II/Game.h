#pragma once
#include <SFML\Graphics.hpp>
#include "StateManager.h"
class App;
class Game : public sf::Drawable
{
public:
	Game(App& app);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	App& m_app;
	StateManager m_statemanager;
};

