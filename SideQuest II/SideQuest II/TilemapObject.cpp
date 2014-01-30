#include "TilemapObject.h"


TilemapObject::TilemapObject(std::string p_name, std::string p_type, sf::Vector2u pos, sf::Vector2u p_size)
: position(pos)
, size(p_size)
, type(p_type)
, name(p_name)
{
}
