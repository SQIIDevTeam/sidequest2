#include "Player.h"


Player::Player(App& app)
: m_texture(app.texturemanager.get("Assets/Game/player.png"))
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s(m_texture);
	target.draw(s,states);
}