#include "App.h"
#include "Config.h"

App::App(Config& c)
{
	m_window.create(sf::VideoMode(c.get<unsigned int>("windowsize_x"), c.get<unsigned int>("windowsize_y")), "SideQuest II");
}

void App::run()
{
	while (m_window.isOpen())
	{
		sf::Event e;
		while (m_window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				m_window.close();
		}

		update();
		render();
	}
}

sf::RenderWindow& App::window()
{
	return m_window;
}

const sf::RenderWindow& App::window() const
{
	return m_window;
}

void App::update()
{

}

void App::render()
{
	m_window.clear();
	m_window.display();
}