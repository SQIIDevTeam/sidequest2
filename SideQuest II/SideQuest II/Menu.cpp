#include "Menu.h"


Menu::Menu(App& app, const sf::Texture& borderTexture, const sf::Vector2f& borderWidth)
: m_borderSprite(borderTexture)
, m_borderWidth(borderWidth)
, m_app(app)
{
}

void Menu::addButton(Button b)
{
	b.setPosition(sf::Vector2f(m_borderWidth.x + 5, m_borderWidth.y + m_buttons.size()*(b.getSize().y + 15)));
	m_buttons.push_back(b);
}

void Menu::addButton(const std::string& texturePath, const std::string& hoverTexturePath, const std::string& fontPath, std::string text)
{
	addButton(Button(m_app, *this, m_app.texturemanager.get(texturePath), m_app.texturemanager.get(hoverTexturePath), m_app.fontmanager.get(fontPath), text));
}

void Menu::setBorderTexture(sf::Texture& texture)
{
	m_borderSprite.setTexture(texture);
}

void Menu::setBorderWidth(sf::Vector2f& width)
{
	m_borderWidth = width;
	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].setPosition(m_borderWidth.x + 5, m_borderWidth.y + i*(m_buttons[0].getSize().y + 15));
	}
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_borderSprite, states);
	
	for (auto& b : m_buttons)
	{
		target.draw(b, states);
	}
}

void Menu::update()
{
	for (auto& b : m_buttons)
		b.update();
}

sf::Vector2f Menu::getSize() const
{
	return sf::Vector2f(m_borderSprite.getTexture()->getSize());
}