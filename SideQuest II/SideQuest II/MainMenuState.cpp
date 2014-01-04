#include "MainMenuState.h"
#include "App.h"

MainMenuState::MainMenuState(App& app)
: State(app)
, m_borderTexture(m_app.texturemanager.get("Assets/Menu/border.png"))
, m_borderSprite(m_borderTexture)
{
	m_borderSprite.setOrigin(m_borderSprite.getLocalBounds().width / 2.f, m_borderSprite.getLocalBounds().height / 2.f);
	m_borderSprite.setPosition(m_app.window.getView().getCenter());
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_borderSprite);
}

void MainMenuState::update()
{
	m_borderSprite.setOrigin(m_borderSprite.getLocalBounds().width / 2.f, m_borderSprite.getLocalBounds().height / 2.f);
	m_borderSprite.setPosition(m_app.window.getView().getCenter());
}