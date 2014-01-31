#include <type_traits>
#include <SFML/Graphics.hpp>

template <typename T>
inline void setOriginCenter(T& sfobject)
{
	sf::FloatRect rect = sfobject.getLocalBounds();
	sfobject.setOrigin((rect.left + rect.width)/2, (rect.top + rect.height)/2);
}