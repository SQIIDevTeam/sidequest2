#include "App.h"
#include "Config.h"
#include "CircleState.h"
#include "RectState.h"

App::App(Config& c)
	: m_accumulator(0)
	, timestep(1.f / 60.f)
	, statemanager(*this)
{
	window.create(sf::VideoMode(c.get<unsigned int>("windowsize_x"), c.get<unsigned int>("windowsize_y")), "SideQuest II");

	statemanager.registerState("circle", std::unique_ptr<State>(new CircleState(*this)));
	statemanager.registerState("rect", std::unique_ptr<State>(new RectState(*this)));
	statemanager.pushState("circle");
}

void App::run()
{
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		float frametime = m_clock.restart().asSeconds();
		m_accumulator += frametime;

		while (m_accumulator >= timestep)
		{
			m_accumulator -= timestep;
			update();
		}	
		render();
	}
}

void App::update()
{
	statemanager.update();
}

void App::render()
{
	window.clear();
	window.draw(statemanager);
	window.display();
}