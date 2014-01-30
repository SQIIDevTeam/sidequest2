#pragma once
#include "State.h"
class StartupState :
	public State
{
public:
	StartupState(App& app);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();

	virtual void handleEvent(sf::Event& event);

private:
	sf::Texture& m_logotex;
	sf::Sprite m_logosprite;
	sf::Font& m_font;
	sf::Text m_continue_text;

	float m_time_elapsed;
};

