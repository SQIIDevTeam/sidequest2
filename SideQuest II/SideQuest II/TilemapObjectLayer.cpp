#include "TilemapObjectLayer.h"


TilemapObjectLayer::TilemapObjectLayer(pugi::xml_node xml)
{
	this->name = xml.attribute("name").as_string();
	auto properties = xml.child("properties");
	for (pugi::xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property"))
	{
		m_properties[prop.attribute("name").as_string()] = prop.attribute("value").as_string();
	}

	for (pugi::xml_node obj = xml.child("object"); obj; obj = obj.next_sibling("object"))
	{
		m_objects.emplace_back(
				obj.attribute("name").as_string(),
				obj.attribute("type").as_string(),
				sf::Vector2u(
					obj.attribute("x").as_uint(),
					obj.attribute("y").as_uint()
				),
				sf::Vector2u(
					obj.attribute("width").as_uint(),
					obj.attribute("height").as_uint()
				)
			);
	}
}

std::vector<TilemapObject> TilemapObjectLayer::getObjects(std::string type)
{
	std::vector<TilemapObject> objects;
	for (auto& object : m_objects)
	{
		if (object.type == type)
			objects.push_back(object);
	}
	return objects;
}