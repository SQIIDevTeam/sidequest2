#pragma once
#include <map>
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Font.hpp>

template<typename T>
class ResourceManager
{
public:
	ResourceManager(){}

	T& get(std::string path);
	const T& get(std::string path) const;
private:
	mutable std::map<std::string, std::unique_ptr<T>> m_resourcemap;
};

template<typename T>
T& ResourceManager<T>::get(std::string path)
{
	auto it = m_resourcemap.find(path);
	if (it == m_resourcemap.end())
	{
		std::unique_ptr<T> res(new T);
		res->loadFromFile(path);
		m_resourcemap[path] = std::move(res);
	}
	return *m_resourcemap[path];
}

template<typename T>
const T& ResourceManager<T>::get(std::string path) const
{
	auto it = m_resourcemap.find(path);
	if (it == m_resourcemap.end())
	{
		m_resourcemap[path] = std::move(std::unique_ptr<T>(new T(path)));
	}
	return m_resourcemap[path];
}

typedef ResourceManager<sf::Texture> TextureManager;
typedef ResourceManager<sf::Font> FontManager;
