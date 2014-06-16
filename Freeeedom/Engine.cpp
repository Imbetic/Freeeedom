#include "stdafx.h"
#include "InputManager.h"
#include "State.h"
#include "GameState.h"


Engine::Engine(void)
{

}


Engine::~Engine(void)
{

}

bool Engine::Initialize()
{
	m_view = new sf::View;
	m_view->setSize(sf::Vector2f(1280, 720));
	m_inputmngr = new InputManager;
	m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "The SHIT");
	m_window->setView(*m_view);
	m_window->setMouseCursorVisible(false);
	m_statemanager.Attach(new GameState(this));
	m_statemanager.SetState("GameState");
	return true;
}

void Engine::Run()
{
	while(m_running)
	{
		sf::Event event;
		if(m_window->pollEvent(event))
		{
			m_inputmngr->UpdateEvents(event);
		}
		UpdateDeltatime();
		m_statemanager.Update(0.01f);
		m_window->clear();
		m_statemanager.Draw();
		m_window->display();
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

};