#include "CreditState.h"
#include "App.h"

CreditState::CreditState(App& app)
: State(app)
, m_font(m_app.fontmanager.get("Assets/Fonts/ALGER.TTF"))
, m_text("patrick246 \nNautha \nMarkusH", m_font, 40)
{
	sf::FloatRect rect(m_text.getLocalBounds());
	m_text.setOrigin((rect.left + rect.width) / 2.f, (rect.top + rect.height) /2.f);
	m_text.setPosition(m_app.window.getView().getCenter());
}

void CreditState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}
void CreditState::update()
{
	sf::FloatRect rect(m_text.getLocalBounds());
	m_text.setOrigin((rect.left + rect.width) / 2.f, (rect.top + rect.height) / 2.f);
	m_text.setPosition(m_app.window.getView().getCenter());

	if (m_app.inputmanager.isKeyHit(sf::Keyboard::Escape))
	{
		m_app.statemanager.popState();
	}
}