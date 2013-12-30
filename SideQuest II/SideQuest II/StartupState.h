#pragma once
#include "State.h"
class StartupState :
	public State
{
public:
	StartupState(App& app);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();
private:

};

