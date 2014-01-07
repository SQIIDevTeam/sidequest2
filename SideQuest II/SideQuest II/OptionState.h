#pragma once
#include "State.h"
class OptionState :
	public State
{
public:
	OptionState(App& app);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update();
private:
	sf::Text m_resText;
	sf::Font& m_font;
	sf::Sprite m_selectionLeft;
	sf::Sprite m_selectionRight;

	std::vector<sf::VideoMode> m_videoModes;
	std::size_t m_desktopResIndex;
	std::size_t m_fullscreenResIndex;
};

