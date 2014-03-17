#include "stdafx.h"
#include "GameState.h"
#include "InputManager.h"
#include "GameObjectManager.h"


GameState::GameState(Engine* engine)
{
	m_engine = engine;
	m_gom = new GameObjectManager(m_engine);
}


GameState::~GameState(void)
{
	m_engine = nullptr;
}

bool GameState::EnterState()
{
	m_gom->Initialize();
	return true;
};

bool GameState::Update(float p_fDeltatime){
	m_gom->Update(p_fDeltatime);
	if(m_engine->m_inputmngr->IsDownK(sf::Keyboard::Escape)){ 
		m_engine->m_running = false;
	}
	return true;
};

void GameState::Draw(){
	m_gom->Draw();

};

void GameState::ExitState(){

};

bool GameState::IsType(const std::string &p_sType){
	if(p_sType == "GameState") return true;
	else return false;

};

std::string GameState::GetCurrentState(){

	return "GameState";

};