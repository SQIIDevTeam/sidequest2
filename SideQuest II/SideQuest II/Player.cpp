#include "Player.h"


Player::Player(App& app)
: m_texture(app.texturemanager.get("Assets/Game/player.png"))
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s(m_texture);
	s.setPosition(m_position);
	target.draw(s,states);
}

void Player::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void Player::setPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
}