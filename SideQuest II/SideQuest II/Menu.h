#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Menu :
	public sf::Drawable,
	public sf::Transformable
{
public:
	Menu(App& app, const sf::Texture& borderTexture, const sf::Vector2f& borderWidth);
	void addButton(Button b);
	void addButton(const std::string& texturePath, const std::string& hoverTexturePath, const std::string& fontPath, std::string text, std::function<void(sf::Vector2f point)> handler);
	void setBorderTexture(sf::Texture& texture);
	void setBorderWidth(sf::Vector2f& width);
	sf::Vector2f getSize() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
private:
	std::vector<Button> m_buttons;
	sf::Sprite m_borderSprite;
	sf::Vector2f m_borderWidth;
	App& m_app;
};

