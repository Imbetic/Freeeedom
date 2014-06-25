#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Humanoid.h"
#include "PlayerControls.h"
#include "Wall.h"

GameObjectManager::GameObjectManager(Engine* engine)
{
	m_engine = engine;
}


GameObjectManager::~GameObjectManager(void)
{

}

bool GameObjectManager::Initialize()
{
	m_walls.push_back(new Wall(sf::Vector2f(0,0), sf::Vector2f(600/2,50/2)));
	m_walls.push_back(new Wall(sf::Vector2f(600/2,0), sf::Vector2f(50/2,500/2)));
	m_walls.push_back(new Wall(sf::Vector2f(0,50/2), sf::Vector2f(50/2,700/2)));
	m_walls.push_back(new Wall(sf::Vector2f(600/2,600/2), sf::Vector2f(50/2,200/2)));
	m_walls.push_back(new Wall(sf::Vector2f(0/2,750/2), sf::Vector2f(600/2,50/2)));

	m_player = new Humanoid(new PlayerControls(m_engine->m_inputmngr, m_engine->m_window));
	
	return true;
};

void GameObjectManager::Update(float deltatime)
{
	m_player->Update(deltatime);
	m_player->WallCollision(m_walls);

	m_engine->m_view->setCenter(m_player->GetPosition());
	m_engine->m_view->setRotation(m_player->GetRotation() - 90);
	m_engine->m_view->setCenter(m_player->GetCameraAnchor());
	m_engine->m_window->setView(*m_engine->m_view);

	for(int i = 0; i<m_walls.size(); i++)
	{
		m_walls.at(i)->Update(m_player);
	}

	

};

void GameObjectManager::Draw()
{
	for(int i = 0; i<m_walls.size(); i++)
	{
		m_walls.at(i)->DrawShadows(m_engine->m_window);
	}
	for(int i = 0; i<m_walls.size(); i++)
	{
		m_walls.at(i)->Draw(m_engine->m_window);
	}

	m_player->Draw(m_engine->m_window);
	
};

void GameObjectManager::Clear()
{
	m_engine = nullptr;
};