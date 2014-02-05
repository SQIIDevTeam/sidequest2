#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include "TilemapObject.h"
#include <pugixml.hpp>
#include "string_op.h"

class TilemapObjectLayer
{
public:
	TilemapObjectLayer(pugi::xml_node xml);

	template<typename T>
	T getProperty(std::string name) const;
public:
	std::string name;
private:
	std::vector<TilemapObject> m_objects;
	std::map<std::string, std::string> m_properties;
};

template<typename T>
T TilemapObjectLayer::getProperty(std::string name) const
{
	auto it = m_properties.find(name);
	if (it != m_properties.end())
	{
		return stringTo<T>(*it);
	}
	return T();
}