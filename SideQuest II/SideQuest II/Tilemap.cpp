#include "Tilemap.h"
#include "App.h"

Tilemap::Tilemap(App& app, std::string filename)
: m_app(app)
{
	if (filename != "")
		loadFromFile(filename);
}

void Tilemap::loadFromFile(std::string filename)
{
	m_doc.load_file(filename.c_str());
	pugi::xml_node map = m_doc.child("map");
	
	// Parse the size
	m_mapsize = sf::Vector2u(map.attribute("width").as_uint(), map.attribute("height").as_uint());
	m_tilesize = sf::Vector2u(map.attribute("tilewidth").as_uint(), map.attribute("tileheight").as_uint());

	pugi::xml_node image = map.child("tileset").child("image");
	std::string tilesetPath = std::string("Assets/Game/Maps/") + image.attribute("source").as_string();
	m_tileset = &m_app.texturemanager.get(tilesetPath);
	m_tilesetsize = sf::Vector2u(image.attribute("width").as_uint(), image.attribute("height").as_uint());

	// Now load the layers
	for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
	{
		pugi::xml_node data = layer.child("data");
		if (std::string(data.attribute("encoding").as_string()) == "csv")
		{
			std::vector<unsigned int> layervec;
			std::stringstream ss(data.text().as_string());
			for (std::string cur; std::getline(ss, cur, ','); layervec.push_back(stringTo<unsigned int>(cur)));
			m_layerdata.push_back(layervec);
		}
	}

	// And the object layers
	for (pugi::xml_node node = map.child("objectgroup"); node; node = node.next_sibling("objectgroup"))
	{
		m_objects.emplace_back(node);
	}
	fillVAs();
}

void Tilemap::fillVAs()
{
	m_layers.clear();
	for (std::size_t i = 0; i < m_layerdata.size(); i++)
	{
		m_layers.emplace_back(sf::Quads, m_mapsize.x * m_mapsize.y * 4);
		for (std::size_t k = 0; k < m_layerdata[i].size(); k++)
		{
			if (m_layerdata[i][k] == 0) continue;

			unsigned int texture_index = m_layerdata[i][k] - 1;
			
			unsigned int tex_x = (texture_index % (m_tilesetsize.x / m_tilesize.x)) * m_tilesize.x;
			unsigned int tex_y = (texture_index / (m_tilesetsize.x / m_tilesize.x)) * m_tilesize.x;

			unsigned int pos_x = (k % m_mapsize.x) * m_tilesize.x*2;
			unsigned int pos_y = (k / m_mapsize.x) * m_tilesize.x*2;

			sf::Vertex* quad = &m_layers[i][k * 4];
			quad[0].position = sf::Vector2f(static_cast<float>(pos_x),						static_cast<float>(pos_y));
			quad[1].position = sf::Vector2f(static_cast<float>(pos_x + m_tilesize.x * 2),	static_cast<float>(pos_y));
			quad[2].position = sf::Vector2f(static_cast<float>(pos_x + m_tilesize.x * 2),	static_cast<float>(pos_y + m_tilesize.y * 2));
			quad[3].position = sf::Vector2f(static_cast<float>(pos_x),						static_cast<float>(pos_y + m_tilesize.y * 2));

			quad[0].texCoords = sf::Vector2f(static_cast<float>(tex_x),						static_cast<float>(tex_y));
			quad[1].texCoords = sf::Vector2f(static_cast<float>(tex_x + m_tilesize.x),		static_cast<float>(tex_y));
			quad[2].texCoords = sf::Vector2f(static_cast<float>(tex_x + m_tilesize.x),		static_cast<float>(tex_y + m_tilesize.y));
			quad[3].texCoords = sf::Vector2f(static_cast<float>(tex_x),						static_cast<float>(tex_y + m_tilesize.y));
		}
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = m_tileset;
	for (std::size_t i = 0; i < m_layers.size(); i++)
		target.draw(m_layers[i], states);
}
