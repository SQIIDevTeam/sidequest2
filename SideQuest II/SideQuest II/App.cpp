#include "App.h"
#include "Config.h"
#include "CircleState.h"
#include "RectState.h"
#include "StartupState.h"
#include "MainMenuState.h"
#include "CreditState.h"
#include "OptionState.h"
#include "PlayState.h"

/**
	Sets up the window, statemanager, inputmanager, etc.
*/
App::App(Config& c)
	: m_accumulator(0)
	, timestep(1.f / 60.f)
	, statemanager(*this)
	, inputmanager(this->window)
	, m_fullscreen(c.get<bool>("fullscreen"))
	, config(c)
{
	if (m_fullscreen)
	{
		sf::VideoMode mode(c.get<unsigned int>("fullscreen_x"), c.get<unsigned int>("fullscreen_x"));
		validateVideoMode(mode);
		window.create(mode, "SideQuest II", sf::Style::Fullscreen);
	}
	else 
	{
		window.create(sf::VideoMode(c.get<unsigned int>("windowsize_x"), c.get<unsigned int>("windowsize_y")), "SideQuest II");
	}
	
	window.setVerticalSyncEnabled(c.get<bool>("vsync"));
	window.clear();
	window.display();

	statemanager.registerState("circle",	std::unique_ptr<State>(new CircleState	(*this)));
	statemanager.registerState("rect",		std::unique_ptr<State>(new RectState	(*this)));
	statemanager.registerState("startup",	std::unique_ptr<State>(new StartupState	(*this)));
	statemanager.registerState("mainmenu",	std::unique_ptr<State>(new MainMenuState(*this)));
	statemanager.registerState("credits",	std::unique_ptr<State>(new CreditState	(*this)));
	statemanager.registerState("options",	std::unique_ptr<State>(new OptionState	(*this)));
	statemanager.registerState("play",		std::unique_ptr<State>(new PlayState	(*this)));
	statemanager.pushState("startup");
}

/**
	Contains the main loop
*/
void App::run()
{
	while (statemanager.isRunning())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				statemanager.setRunning(false);
			}
			else if (e.type == sf::Event::Resized)
			{
				onResize();
				statemanager.handleEvent(e);
			}
			else
			{
				statemanager.handleEvent(e);
			}
		}

		float frametime = m_clock.restart().asSeconds();
		m_accumulator += frametime;

		while (m_accumulator >= timestep)
		{
			m_accumulator -= timestep;
			window.setTitle("SideQuest II - Frametime: " + toString(frametime) + " - FPS: " + toString(1 / frametime));
			inputmanager.update();
			update();
		}	
		render();
	}
	if (!statemanager.isRunning())
		window.close();

}

/**
	Updates the game states, and sets the view to match the window size every frame
*/
void App::update()
{
	statemanager.update();

	if (inputmanager.isKeyHit(sf::Keyboard::F4))
	{
		setFullscreen(!m_fullscreen);
	}

	sf::View view(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	view.setCenter(window.getView().getCenter());
	window.setView(view);
}

/**
	Renders the current state to the screen
*/
void App::render()
{
	window.clear();
	window.draw(statemanager);
	window.display();
}

void App::onResize()
{
	sf::VideoMode mode(window.getSize().x, window.getSize().y);
	validateVideoMode(mode);
	window.setSize(sf::Vector2u(mode.width, mode.height));
}

void App::setFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		m_fullscreen = true;
		sf::VideoMode mode(config.get<unsigned int>("fullscreen_x"), config.get<unsigned int>("fullscreen_y"));
		validateVideoMode(mode);
		window.create(mode, "SideQuest II", sf::Style::Fullscreen);
		window.setVerticalSyncEnabled(config.get<bool>("vsync"));
		window.clear();
		window.display();
		return;
	}
	m_fullscreen = false;
	sf::VideoMode mode(config.get<unsigned int>("windowsize_x"), config.get<unsigned int>("windowsize_y"));
	validateVideoMode(mode);
	window.create(mode, "SideQuest II", sf::Style::Default);
	window.clear();
	window.display();
}

void App::validateVideoMode(sf::VideoMode& mode)
{
	if (mode.width > 1920)
		mode.width = 1920;
	else if (mode.width < 800)
		mode.width = 800;

	if (mode.height > 1080)
		mode.height = 1080;
	else if (mode.height < 600)
		mode.height = 600;

	if (m_fullscreen && mode.isValid())
	{
		const std::vector<sf::VideoMode>& fullscreen_modes = sf::VideoMode::getFullscreenModes();

		for (std::size_t i = 1; i < fullscreen_modes.size(); i++)
		{
			if (fullscreen_modes[i].width < mode.width && fullscreen_modes[i].height < mode.height && fullscreen_modes[i - 1].width <= 1920 && fullscreen_modes[i - 1].height <= 1080)
			{
				mode = fullscreen_modes[i - 1];
				break;
			}
		}
	}
}

///
/// Returns the current fullscreen state
///
bool App::isFullscreen() const
{
	return m_fullscreen;
}