#pragma once
#include "StateManager.h"

class InputManager;

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void Run();
	void Cleanup();
	void UpdateDeltatime();

	bool m_running;
	float m_deltatime;

	StateManager m_statemanager;

	sf::RenderWindow* m_window;
	InputManager* m_inputmngr;

	sf::Clock m_clock;

	sf::View* m_view;
};

