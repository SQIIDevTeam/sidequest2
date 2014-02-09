#include "PlayState.h"
#include "App.h"
#include <cassert>
PlayState::PlayState(App& app)
: State(app)
, m_tilemap(app)
, m_player(app)
{
	m_tilemap.loadFromFile("Assets/Game/Maps/debug_playground.tmx");
	auto spawns = m_tilemap.getObjects("spawn");
	assert(spawns.size() == 1 && "There is more than one spawn point");
	sf::Vector2f spawnpoint = sf::Vector2f(spawns[0].position.x*2, spawns[0].position.y * 2);
	m_player.setPosition(spawnpoint);
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_tilemap, states);
	target.draw(m_player, states);
}

void PlayState::update()
{

}