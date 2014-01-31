#include "StateManager.h"
#include "App.h"
#include "math.h"

#include <stdexcept>

StateManager::StateManager(App& app)
: m_app(app)
, m_transitionAlpha(255)
, m_transitionState(TransitionState::NONE)
, m_transitionTimeSec(0)
, m_running(true)
{
}

void StateManager::registerState(std::string id, std::unique_ptr<State> state)
{
	if (!state)
	{
		throw std::runtime_error("StateManager::registerState: state is nullptr");
	}
	if (id == "")
	{
		throw std::runtime_error("StateManager::registerState: id is empty");
	}
	if (m_registered.find(id) != m_registered.end())
	{
		throw std::runtime_error("StateManager::registerState: state already registered, id is used");
	}

	m_registered[id] = std::move(state);
}

void StateManager::pushState(std::string id)
{
	if (m_registered.find(id) == m_registered.end())
	{
		throw std::runtime_error("StateManager::pushState: id does not exist: " + id);
	}
	if (m_transitionState == TransitionState::NONE)
	{
		// Create the source texture, black if no state is present
		m_transitionState = TransitionState::IN_PROGRESS_BLEND_DOWN;
		m_transitionTextureSource.create(m_app.window.getSize().x, m_app.window.getSize().y);
		//m_transitionTextureSource.setView(m_app.window.getView());
		m_transitionTextureSource.clear();
		if (!m_stack.empty())
		{
			m_transitionTextureSource.draw(*m_stack.top());	
		}
		m_transitionTextureSource.display();

		// Create the destination texture
		m_transitionTextureDest.create(m_app.window.getSize().x, m_app.window.getSize().y);
		//m_transitionTextureDest.setView(m_app.window.getView());
		m_transitionTextureDest.clear();
		// Update the next state in case ít hasn't caught up with some changes (e.g. window resize)
		m_registered[id]->update();
		m_transitionTextureDest.draw(*m_registered[id]);
		m_transitionTextureDest.display();

		// Set the state
		m_transitionAction = TransitionAction::PUSH;
		m_transitionNextState = m_registered[id].get();
	}
	
	//m_stack.push(m_registered[id].get());
}

void StateManager::popState()
{
	if (m_transitionState == TransitionState::NONE)
	{
		// Create the source texture, black if no state is present
		m_transitionState = TransitionState::IN_PROGRESS_BLEND_DOWN;
		if (m_transitionTextureSource.getSize() != m_app.window.getSize())
		{
			m_transitionTextureSource.create(m_app.window.getSize().x, m_app.window.getSize().y);
		}
		
		//m_transitionTextureSource.setView(m_app.window.getView());
		m_transitionTextureSource.clear();
		if (!m_stack.empty())
		{
			m_transitionTextureSource.draw(*m_stack.top());
		}
		m_transitionTextureSource.display();

		// Create the destination texture
		if (m_transitionTextureDest.getSize() != m_app.window.getSize())
		{
			m_transitionTextureDest.create(m_app.window.getSize().x, m_app.window.getSize().y);
		}
		//m_transitionTextureDest.setView(m_app.window.getView());
		m_transitionTextureDest.clear();
		// Update the destination state in case it hasn't caught up with some changes
		m_stack[1]->update();
		m_transitionTextureDest.draw(*m_stack[1]);
		m_transitionTextureDest.display();

		// Set the state
		m_transitionAction = TransitionAction::POP;
		m_transitionNextState = nullptr;
	}
	//m_stack.pop();
}

void StateManager::setTopState(std::string id)
{
	if (m_transitionState == TransitionState::NONE)
	{
		// Create the source texture, black if no state is present
		m_transitionState = TransitionState::IN_PROGRESS_BLEND_DOWN;
		m_transitionTextureSource.create(m_app.window.getSize().x, m_app.window.getSize().y);
		//m_transitionTextureSource.setView(m_app.window.getView());
		m_transitionTextureSource.clear();
		if (!m_stack.empty())
		{
			m_transitionTextureSource.draw(*m_stack.top());
		}
		m_transitionTextureSource.display();

		// Create the destination texture
		m_transitionTextureDest.create(m_app.window.getSize().x, m_app.window.getSize().y);
		//m_transitionTextureDest.setView(m_app.window.getView());
		m_transitionTextureDest.clear();
		// Update the next state in case ít hasn't caught up with some changes (e.g. window resize)
		m_registered[id]->update();
		m_transitionTextureDest.draw(*m_registered[id]);
		m_transitionTextureDest.display();

		// Set the state
		m_transitionAction = TransitionAction::SET;
		m_transitionNextState = m_registered[id].get();
	}
	/*
	m_stack.pop();
	if (m_registered.find(id) == m_registered.end())
	{
		throw std::runtime_error("StateManager::pushState: id does not exist: " + id);
	}
	m_stack.push(m_registered[id].get());*/
}


void StateManager::update()
{
	if (m_transitionState == TransitionState::NONE)
	{
		m_stack.top()->update();
	}
	if (m_transitionState == TransitionState::IN_PROGRESS_BLEND_DOWN)
	{
		m_transitionAlpha = static_cast<int>(lerp(static_cast<int>(m_transitionAlpha), 0.f, m_transitionTimeSec * m_app.config.get<float>("transition_mul")) - 0.5f);
		m_transitionTimeSec += m_app.timestep;
	
		if (m_transitionAlpha <= 10)
		{
			if (m_transitionAction == TransitionAction::SHUTDOWN)
			{
				while (!m_stack.empty())
				{
					m_stack.top()->onExit();
					m_stack.pop();
					if(!m_stack.empty()) 
						m_stack.top()->onEnter();
				}
				m_running = false;
			}
			else
			{
				m_transitionState = TransitionState::IN_PROGRESS_BLEND_UP;
				m_transitionAlpha = 0;
				m_transitionTimeSec = 0;
			}
		}
	}
	if (m_transitionState == TransitionState::IN_PROGRESS_BLEND_UP)
	{
		m_transitionAlpha = static_cast<int>(lerp(static_cast<int>(m_transitionAlpha), 255.f, m_transitionTimeSec * m_app.config.get<float>("transition_mul")) + 0.5f);
		m_transitionTimeSec += m_app.timestep;
		if (m_transitionAlpha >= 240)
		{
			m_transitionState = TransitionState::NONE;
			m_transitionAlpha = 255;
			m_transitionTimeSec = 0;
			if (m_transitionAction == TransitionAction::PUSH)
			{
				if (!m_stack.empty())
					m_stack.top()->onExit();
				m_stack.push(m_transitionNextState);
				m_transitionNextState->onEnter();
			}
			else if (m_transitionAction == TransitionAction::POP)
			{
				m_stack.top()->onExit();
				m_stack.pop();
				m_stack.top()->onEnter();
			}
			else if (m_transitionAction == TransitionAction::SET)
			{
				m_stack.top()->onExit();
				m_stack.pop();
				m_stack.push(m_transitionNextState);
				m_stack.top()->onEnter();
			}
		}
	}
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_transitionState == TransitionState::NONE)
	{
		target.draw(*m_stack.top());
	} 
	else if (m_transitionState == TransitionState::IN_PROGRESS_BLEND_DOWN)
	{
		sf::Sprite source(m_transitionTextureSource.getTexture());
		source.setColor(sf::Color(255, 255, 255, m_transitionAlpha));
		
		target.draw(source);
	}
	else
	{
		sf::Sprite dest(m_transitionTextureDest.getTexture());
		dest.setColor(sf::Color(255, 255, 255, m_transitionAlpha));

		target.draw(dest);
	}
}


bool StateManager::isRunning() const
{
	return m_running;
}

void StateManager::setRunning(bool running)
{
	if (!running && m_transitionState == TransitionState::NONE)
	{
		// Create the source texture, black if no state is present
		m_transitionState = TransitionState::IN_PROGRESS_BLEND_DOWN;
		m_transitionTextureSource.create(m_app.window.getSize().x, m_app.window.getSize().y);
		//m_transitionTextureSource.setView(m_app.window.getView());
		m_transitionTextureSource.clear();
		if (!m_stack.empty())
		{
			m_transitionTextureSource.draw(*m_stack.top());
		}
		m_transitionTextureSource.display();

		// Create the destination texture
		m_transitionTextureDest.create(m_app.window.getSize().x, m_app.window.getSize().y);
		//m_transitionTextureDest.setView(m_app.window.getView());
		m_transitionTextureDest.clear();
		m_transitionTextureDest.display();

		// Set the state
		m_transitionAction = TransitionAction::SHUTDOWN;
	}
	else
	{
		m_running = true;
	}
}

void StateManager::handleEvent(sf::Event& event)
{
	for (auto& state : m_stack)
	{
		state->handleEvent(event);
	}
}
