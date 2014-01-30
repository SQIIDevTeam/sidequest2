#include "OptionState.h"
#include "App.h"
#include "sfHelper.h"
#include <string>
OptionState::OptionState(App& app)
: State(app)
, m_fullscreenResIndex(0)
, m_desktopResIndex(0)
, m_font(m_app.fontmanager.get("Assets/Fonts/ALGER.TTF"))
, m_selectionLeft(m_app.texturemanager.get("Assets/Option/selector_left.png"))
, m_selectionRight(m_app.texturemanager.get("Assets/Option/selector_right.png"))
, m_resText("", m_app.fontmanager.get("Assets/Fonts/ALGER.TTF"))
{
	// Select all VideoModes with 32 Bit per Pixel, no one wants the others
	/*std::vector<sf::VideoMode> videoModes(sf::VideoMode::getFullscreenModes());
	std::copy_if(videoModes.begin(), videoModes.end(), m_videoModes.begin(), [](sf::VideoMode mode){
		return mode.bitsPerPixel == 32;
	});*/

	for (auto& mode : sf::VideoMode::getFullscreenModes())
	{
		if (mode.bitsPerPixel == 32 && mode.width != 0 && mode.height != 0) m_videoModes.push_back(mode);
	}

	// Look for the values currently set
	std::size_t i = 0;
	for (auto& vm : m_videoModes)
	{
		if (vm.width == m_app.config.get<unsigned int>("windowsize_x") && vm.height == m_app.config.get<unsigned int>("windowsize_y"))
		{
			m_desktopResIndex = i;
			break;
		}
		if (vm.width == m_app.config.get<unsigned int>("fullscreen_x") && vm.height == m_app.config.get<unsigned int>("fullscreen_y"))
		{
			m_fullscreenResIndex = i;
			break;
		}
		++i;
	}
	m_selectionLeft.scale(0.25, 0.25);
	m_selectionRight.scale(0.25, 0.25);
	//m_resText.setOrigin(m_resText.getLocalBounds().left + m_resText.getLocalBounds().width, m_resText.getLocalBounds().top + m_resText.getLocalBounds().height);
	//m_resText.setPosition(m_app.window.getView().getCenter().x, 10);
}

void OptionState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_resText, states);
	target.draw(m_selectionLeft, states);
	target.draw(m_selectionRight, states);
}

void OptionState::update()
{
	/*
	m_resText.setColor(sf::Color::White);
	m_resText.setString(toString(m_videoModes[m_fullscreenResIndex].width) + "x" + toString(m_videoModes[m_fullscreenResIndex].height));
	m_resText.setOrigin((m_resText.getLocalBounds().left + m_resText.getLocalBounds().width)/2.f, (m_resText.getLocalBounds().top + m_resText.getLocalBounds().height)/2.f);
	m_resText.setPosition(m_app.window.getView().getCenter().x, 50);

	m_selectionLeft.setPosition(m_resText.getPosition().x - (m_resText.getLocalBounds().left + m_resText.getLocalBounds().width) - m_selectionLeft.getLocalBounds().width, m_resText.getPosition().y - m_resText.getLocalBounds().height);
	m_selectionRight.setPosition(m_resText.getPosition().x + m_selectionLeft.getLocalBounds().width, m_resText.getPosition().y - m_resText.getLocalBounds().height);
	*/
	m_resText.setString(toString(m_videoModes[m_fullscreenResIndex].width) + "x" + toString(m_videoModes[m_fullscreenResIndex].height));
	setOriginCenter(m_resText);
	m_resText.setPosition(m_app.window.getView().getCenter().x, 50);

	setOriginCenter(m_selectionLeft);
	m_selectionLeft.setPosition(m_resText.getPosition().x - (m_resText.getLocalBounds().left + m_resText.getLocalBounds().width) / 2 - m_selectionLeft.getLocalBounds().width/2, m_resText.getPosition().y);

	setOriginCenter(m_selectionRight);
	m_selectionRight.setPosition(m_resText.getPosition().x + (m_resText.getLocalBounds().left + m_resText.getLocalBounds().width) / 2 + m_selectionRight.getLocalBounds().width / 2, m_resText.getPosition().y);
	
	if (m_selectionRight.getGlobalBounds().contains(m_app.inputmanager.getMousePos()) && m_app.inputmanager.isButtonHit(sf::Mouse::Left))
	{
		if (m_fullscreenResIndex == 0)
			m_fullscreenResIndex = m_videoModes.size() - 1;
		else
			m_fullscreenResIndex--;
	}

	if (m_selectionLeft.getGlobalBounds().contains(m_app.inputmanager.getMousePos()) && m_app.inputmanager.isButtonHit(sf::Mouse::Left))
	{
		if (m_fullscreenResIndex == m_videoModes.size() - 1)
			m_fullscreenResIndex = 0;
		else
			m_fullscreenResIndex++;
	}
}
