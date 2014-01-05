#include "Button.h"
#include "Menu.h"

Button::Button(App& app, Menu& menu, sf::Texture& texture, sf::Texture& hoverTexture, const sf::Font& font, const std::string str, std::function<void(sf::Vector2f point)> handler)
: m_app(app)
, m_text(str, font)
, m_sprite(texture)
, m_normalTexture(texture)
, m_hoverTexture(hoverTexture)
, m_menu(menu)
, m_handler(handler)
{
	sf::FloatRect rect(m_text.getLocalBounds());
	m_text.setOrigin((rect.left + rect.width) / 2.f, (rect.top + rect.height) / 2.f);
	m_text.setPosition(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
}

void Button::setText(const std::string& text)
{
	m_text.setString(text);
}

void Button::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

void Button::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void Button::setHandler(std::function<void(sf::Vector2f point)> handler)
{
	m_handler = handler;
}

void Button::update()
{
	sf::FloatRect bounds(getTransform().transformRect(m_sprite.getGlobalBounds()));
	bounds = m_menu.getTransform().transformRect(bounds);
	if (bounds.contains(m_app.inputmanager.getMousePos()))
	{
		if (m_app.inputmanager.isButtonHit(sf::Mouse::Left))
		{
			if (m_handler)
			{
				sf::Vector2f clickAbsolute(m_app.inputmanager.getMousePos());
				sf::Vector2f clickRelative(clickAbsolute.x - m_sprite.getGlobalBounds().width, clickAbsolute.y - m_sprite.getGlobalBounds().height);
				m_handler(clickRelative);
			}
		}
		m_sprite.setTexture(m_hoverTexture);
	}
	else 
	{
		m_sprite.setTexture(m_normalTexture);
	}
	
	sf::FloatRect rect(m_text.getLocalBounds());
	m_text.setOrigin((rect.left + rect.width) / 2.f, (rect.top + rect.height) / 2.f);
	
	m_text.setPosition(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
}


sf::Vector2f Button::getSize() const
{
	sf::FloatRect rect = m_sprite.getLocalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
	target.draw(m_text, states);
}
