#pragma once
#include "State.h"
#include "Tilemap.h"


class PlayState :
	public State
{
public:
	PlayState(App& app);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();

private:
	Tilemap m_tilemap;
};

