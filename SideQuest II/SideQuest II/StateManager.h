#pragma once
#include <map>
#include <memory>
#include "Stack.h"
#include "State.h"

class StateManager : public sf::Drawable
{
public:
	StateManager(App& app);

	void registerState(std::string id, std::unique_ptr<State> state);
	
	void pushState(std::string id);
	void popState();
	void setTopState(std::string id);

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isRunning() const;
	void setRunning(bool running);

private:
	std::map<std::string, std::unique_ptr<State>> m_registered;
	Stack<State*> m_stack;

	bool m_running;
	App& m_app;

	// Transition stuff
	enum class TransitionState
	{
		NONE,
		IN_PROGRESS_BLEND_DOWN,
		IN_PROGRESS_BLEND_UP
	};
	TransitionState m_transitionState;
	sf::RenderTexture m_transitionTextureSource;
	sf::RenderTexture m_transitionTextureDest;
	State* m_transitionNextState;
	int m_transitionAlpha;
	float m_transitionTimeSec;
	enum class TransitionAction
	{
		PUSH,
		POP,
		SET
	};
	TransitionAction m_transitionAction;
};

