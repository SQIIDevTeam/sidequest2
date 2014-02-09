#pragma once
#include <string>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
#include "TilemapObject.h"
#include "TilemapObjectLayer.h"

class App;


class Tilemap
	: public sf::Drawable
{
public:
	Tilemap(App& app, std::string filename = "");

	void loadFromFile(std::string filename);
	void fillVAs();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<TilemapObject> getObjects(std::string type);
private:
	pugi::xml_document m_doc;
	sf::Texture* m_tileset;
	App& m_app;

	// Map data
	sf::Vector2u m_mapsize;
	sf::Vector2u m_tilesize;
	sf::Vector2u m_tilesetsize;

	std::vector<sf::VertexArray> m_layers;
	std::vector<std::vector<unsigned int>> m_layerdata;
	std::vector<TilemapObjectLayer> m_objects;
};

