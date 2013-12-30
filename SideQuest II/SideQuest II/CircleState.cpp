#include "CircleState.h"
#include "App.h"

CircleState::CircleState(App& app)
: State(app)
{
}

void CircleState::update()
{
		m_app.statemanager.pushState("rect");		
}

void CircleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape shape;
	shape.setRadius(500);
	shape.setFillColor(sf::Color::Red);
	shape.setPointCount(50);
	target.draw(shape, states);
}