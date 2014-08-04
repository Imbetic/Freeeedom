#include "stdafx.h"
#include "GameOverState.h"
#include "InputManager.h"


GameOverState::GameOverState(Engine* engine)
{
	m_engine = engine;
}


GameOverState::~GameOverState(void)
{
	m_engine = nullptr;
}

bool GameOverState::EnterState()
{
	m_engine->m_statemanager.SetNextState("GameOver");
	return true;
};

bool GameOverState::Update(float p_fDeltatime)
{
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Escape)){ 
		m_engine->m_running = false;
	}
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::A)){ 
		m_engine->m_statemanager.SetState("GameState");
	}
	return true;
};

void GameOverState::Draw()
{
	m_engine->m_window->clear(sf::Color::Red);
};

void GameOverState::ExitState()
{
	m_engine = nullptr;
};

bool GameOverState::IsType(const std::string &p_sType)
{
	if(p_sType == "GameOver") return true;
	else return false;
};

std::string GameOverState::GetCurrentState()
{
	return "GameOver";
};