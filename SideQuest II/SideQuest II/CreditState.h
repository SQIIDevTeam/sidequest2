#pragma once
#include "State.h"
class CreditState :
	public State
{
public:
	CreditState(App& app);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();

private:
	sf::Font& m_font;
	sf::Text m_text;
};

