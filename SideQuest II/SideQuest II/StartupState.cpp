#include "StartupState.h"
#include "App.h"

StartupState::StartupState(App& app)
: State(app)
, m_logotex(m_app.texturemanager.get("Assets/Startup/logo.png"))
, m_logosprite(m_logotex)
, m_font(m_app.fontmanager.get("Assets/Fonts/ALGER.TTF"))
, m_continue_text("Press Enter to continue...", m_font)
, m_time_elapsed(0)
{
	sf::FloatRect textRect = m_continue_text.getLocalBounds();
	m_continue_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	m_continue_text.setPosition(sf::Vector2f(m_app.window.getSize().x / 2.f, m_app.window.getSize().y - 50.f));
}

void StartupState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_logosprite, states);
	target.draw(m_continue_text, states);
}

void StartupState::update()
{
	m_time_elapsed += m_app.timestep;

	m_continue_text.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>((sinf(m_time_elapsed * 3.f)+1.3f)/2.3f * 255)));
	
	if (m_app.inputmanager.isKeyHit(sf::Keyboard::Return))
	{
		m_app.statemanager.setTopState("mainmenu");
	}
}

void StartupState::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		m_logosprite.setOrigin(m_logosprite.getLocalBounds().width / 2.f, m_logosprite.getLocalBounds().height / 2.f);
		m_logosprite.setPosition(m_app.window.getView().getCenter());
	}
}
