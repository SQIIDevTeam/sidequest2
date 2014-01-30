#pragma once
#include <SFML/System.hpp>
#include <string>
struct TilemapObject
{
	// No implementation, should never be called
	TilemapObject();

	TilemapObject(std::string p_name, std::string p_type, sf::Vector2u pos, sf::Vector2u p_size);

	sf::Vector2u position;
	sf::Vector2u size;
	std::string name;
	std::string type;
};

