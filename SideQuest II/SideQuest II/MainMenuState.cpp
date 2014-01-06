#include "MainMenuState.h"
#include "App.h"

MainMenuState::MainMenuState(App& app)
: State(app)
, m_borderTexture(m_app.texturemanager.get("Assets/Menu/border.png"))
, m_menu(app, m_borderTexture, sf::Vector2f(45.f, 50.f))
{
	m_menu.setOrigin(m_menu.getSize().x / 2.f, m_menu.getSize().y / 2.f);
	m_menu.setPosition(m_app.window.getView().getCenter());

	m_menu.addButton("Assets/Menu/button.png", "Assets/Menu/button_hover.png", "Assets/Fonts/ALGER.ttf", "Play", [&](sf::Vector2f&){
		
	});
	m_menu.addButton("Assets/Menu/button.png", "Assets/Menu/button_hover.png", "Assets/Fonts/ALGER.ttf", "Options", [&](sf::Vector2f&){

	});
	m_menu.addButton("Assets/Menu/button.png", "Assets/Menu/button_hover.png", "Assets/Fonts/ALGER.ttf", "Credits", [&](sf::Vector2f&){
		m_app.statemanager.pushState("credits");
	});
	m_menu.addButton("Assets/Menu/button.png", "Assets/Menu/button_hover.png", "Assets/Fonts/ALGER.ttf", "Exit", [&](sf::Vector2f&){
		m_app.statemanager.setRunning(false);
	});
}

void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_menu);
}

void MainMenuState::update()
{
	m_menu.setOrigin(m_menu.getSize().x / 2.f, m_menu.getSize().y / 2.f);
	m_menu.setPosition(m_app.window.getView().getCenter());
	m_menu.update();
}