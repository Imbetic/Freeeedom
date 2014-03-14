#include "stdafx.h"
#include "InputManager.h"


Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}

bool Engine::Initialize()
{
	m_inputmngr = new InputManager;
	m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "The SHIT");
	return true;
}

void Engine::Run(){
	while(m_running){

		UpdateDeltatime();
		m_statemanager.Update(0.016f);
		m_window->clear();
	}
};

void Engine::Cleanup(){
	if(m_inputmngr!=nullptr){
		delete m_inputmngr;
		m_inputmngr = nullptr;
	}
	if(m_window!=nullptr){
		delete m_window;
		m_window = nullptr;
	}
}

void Engine::UpdateDeltatime(){};