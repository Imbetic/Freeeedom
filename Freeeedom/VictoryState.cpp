#include "stdafx.h"
#include "VictoryState.h"
#include "InputManager.h"
#include "Engine.h"

VictoryState::VictoryState(Engine* engine)
{
	m_engine = engine;
}


VictoryState::~VictoryState(void)
{
	m_engine = nullptr;
}

bool VictoryState::EnterState()
{
	m_engine->m_view->setCenter(sf::Vector2f(1920/2,1080/2));
	m_engine->m_view->setRotation(0);
	m_engine->m_window->setView(*m_engine->m_view);

	m_texttexture.loadFromFile("../data/VictoryText.png");
	m_text.setTexture(m_texttexture);
	m_text.setPosition(100,200);
	return true;
};

bool VictoryState::Update(float p_fDeltatime)
{
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Escape)){ 
		m_engine->m_running = false;
	}
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Return)){ 
		m_engine->m_statemanager.SetNextState("StartMenu");
	}
	return true;
};

void VictoryState::Draw()
{
	m_engine->m_window->clear(sf::Color::Green);
	m_engine->m_window->draw(m_text);
};

void VictoryState::ExitState()
{

};

bool VictoryState::IsType(const std::string &p_sType)
{
	if(p_sType == "VictoryState") return true;
	else return false;
};

std::string VictoryState::GetCurrentState()
{
	return "VictoryState";
};