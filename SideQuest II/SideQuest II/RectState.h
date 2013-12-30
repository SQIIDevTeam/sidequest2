#pragma once
#include "State.h"
#include "App.h"
class RectState :
	public State
{
public:
	RectState(App& app);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();
};

