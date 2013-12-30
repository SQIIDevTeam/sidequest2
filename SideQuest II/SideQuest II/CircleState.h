#pragma once
#include "State.h"
class CircleState :
	public State
{
public:
	CircleState(App& app);
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

