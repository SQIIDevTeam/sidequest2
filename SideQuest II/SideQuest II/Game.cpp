#include "Game.h"
#include "App.h"
#include "CircleState.h"

Game::Game(App& app)
: m_app(app)
{
	m_statemanager.registerState("circle", std::unique_ptr<State>(new CircleState(app)));

	m_statemanager.pushState("circle");
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_statemanager);
}

void Game::update()
{
	m_statemanager.update();
}