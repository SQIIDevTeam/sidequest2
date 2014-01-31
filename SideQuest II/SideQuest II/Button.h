#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "App.h"
class Menu;

class Button :
	public sf::Drawable,
	public sf::Transformable
{
public:
	Button(App& app, Menu& menu, sf::Texture& texture, sf::Texture& hoverTexture, const sf::Font& font, std::string str, std::function<void(sf::Vector2f point)> handler);
	void setText(const std::string& text);
	void setTexture(const sf::Texture& tex);
	void setFont(const sf::Font& font);
	void setHandler(std::function<void(sf::Vector2f point)> handler);

	void update();
	
	sf::Vector2f getSize() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Text m_text;
	sf::Sprite m_sprite;
	sf::Texture& m_normalTexture;
	sf::Texture& m_hoverTexture;
	std::function<void(sf::Vector2f point)> m_handler;
	App& m_app;
	Menu& m_menu;
};

