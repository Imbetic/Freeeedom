#include "stdafx.h"
#include "InputManager.h"
#include "State.h"
#include "GameState.h"
#include "GameOverState.h"
#include "StartMenu.h"
#include "VictoryState.h"


Engine::Engine(void)
{

}


Engine::~Engine(void)
{

}

bool Engine::Initialize()
{
	m_view = new sf::View;
	m_view->setSize(sf::Vector2f(1920, 1080));
	m_inputmngr = new InputManager;
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "The SHIT");
	m_window->setFramerateLimit(60);
	m_window->setView(*m_view);
	m_window->setMouseCursorVisible(false);
	m_statemanager.Attach(new StartMenu(this));
	m_statemanager.Attach(new GameState(this));
	m_statemanager.Attach(new GameOverState(this));
	m_statemanager.Attach(new VictoryState(this));
	m_statemanager.SetState("StartMenu");
	m_statemanager.SetNextState("StartMenu");
	m_deltatime = 0;
	return true;
}

void Engine::Run()
{
	while(m_running)
	{
		sf::Event event;
		while(m_window->pollEvent(event))
		{
			m_inputmngr->UpdateEvents(event);
		}
		UpdateDeltatime();
		m_statemanager.Update(m_deltatime);
		m_window->clear(sf::Color(130, 195, 255, 255));
		m_statemanager.Draw();
		m_window->display();
		if(m_statemanager.NextState() != m_statemanager.CurrentState())
		{
			m_statemanager.GetCurrentState()->ExitState();
			m_statemanager.SetState(m_statemanager.NextState());
		}
	}
};


void Engine::Cleanup()
{
	if(m_inputmngr!=nullptr){
		delete m_inputmngr;
		m_inputmngr = nullptr;
	}
	if(m_window!=nullptr){
		delete m_window;
		m_window = nullptr;
	}
	if(m_view != nullptr){
		delete m_view;
		m_view = nullptr;
	}
}

void Engine::UpdateDeltatime()
{
	m_deltatime = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();
};