#include "OptionState.h"
#include "App.h"

OptionState::OptionState(App& app)
: State(app)
, m_fullscreenResIndex(0)
, m_desktopResIndex(0)
, m_font(m_app.fontmanager.get("Assets/Fonts/ALGER.TTF"))
, m_videoModes(sf::VideoMode::getFullscreenModes().size())
{
	// Select all VideoModes with 32 Bit per Pixel, no one wants the others
	std::vector<sf::VideoMode> videoModes(sf::VideoMode::getFullscreenModes());
	std::copy_if(videoModes.begin(), videoModes.end(), m_videoModes.begin(), [](sf::VideoMode mode){
		return mode.bitsPerPixel == 32;
	});

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
}

void OptionState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void OptionState::update()
{

}