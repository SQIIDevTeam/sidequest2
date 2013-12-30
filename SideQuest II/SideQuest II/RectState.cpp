#include "RectState.h"


RectState::RectState(App& app)
: State(app)
{
}

void RectState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Blue);
	shape.setSize(sf::Vector2f(500, 500));
	shape.setPosition(sf::Vector2f(100, 100));
	target.draw(shape);
}

void RectState::update()
{
	m_app.statemanager.popState();
}