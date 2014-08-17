#include "stdafx.h"
#include "StartMenu.h"
#include "Engine.h"
#include "Inputmanager.h"

StartMenu::StartMenu(Engine* p_engine)
{
	m_engine = p_engine;
}

StartMenu::~StartMenu(void)
{
	m_engine = nullptr;
}

bool StartMenu::EnterState()
{
	m_engine->m_view->setCenter(sf::Vector2f(1920/2,1080/2));
	m_engine->m_view->setRotation(0);
	m_engine->m_window->setView(*m_engine->m_view);

	m_texttexture.loadFromFile("../data/StartMenuText.png");
	m_text.setTexture(m_texttexture);
	m_text.setPosition(100,200);
	return true;
}

void StartMenu::ExitState()
{

}

bool StartMenu::Update(float p_fDeltatime)
{
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Escape)){ 
		m_engine->m_running = false;
	}
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Space)){ 
		m_engine->m_statemanager.SetNextState("GameState");
	}
	return true;
}

void StartMenu::Draw()
{
	m_engine->m_window->clear(sf::Color::Blue);
	m_engine->m_window->draw(m_text);
}

bool StartMenu::IsType(const std::string &p_sType)
{
	return(p_sType == "StartMenu");
}

std::string StartMenu::GetCurrentState()
{
	return "StartMenu";
}