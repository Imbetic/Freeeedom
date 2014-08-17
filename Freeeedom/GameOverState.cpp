#include "stdafx.h"
#include "GameOverState.h"
#include "InputManager.h"
#include "Engine.h"


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
	m_engine->m_view->setCenter(sf::Vector2f(1920/2,1080/2));
	m_engine->m_view->setRotation(0);
	m_engine->m_window->setView(*m_engine->m_view);

	m_texttexture.loadFromFile("../data/GameOverText.png");
	m_text.setTexture(m_texttexture);
	m_text.setPosition(100,200);
	return true;
};

bool GameOverState::Update(float p_fDeltatime)
{
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Escape)){ 
		m_engine->m_running = false;
	}
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Space)){ 
		m_engine->m_statemanager.SetNextState("GameState");
	}
	return true;
};

void GameOverState::Draw()
{
	m_engine->m_window->clear(sf::Color::Red);
	m_engine->m_window->draw(m_text);
};

void GameOverState::ExitState()
{

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