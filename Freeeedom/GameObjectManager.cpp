#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "PlayerObject.h"
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
	m_walls.push_back(new Wall(sf::Vector2f(0,0), sf::Vector2f(500,50)));
	m_walls.push_back(new Wall(sf::Vector2f(600,0), sf::Vector2f(50,500)));
	m_walls.push_back(new Wall(sf::Vector2f(500,500), sf::Vector2f(100,200)));
	m_walls.push_back(new Wall(sf::Vector2f(600,600), sf::Vector2f(100,200)));
	//m_walls.push_back(new Wall(sf::Vector2f(600,800), sf::Vector2f(200,100)));

	m_player = new PlayerObject(m_engine->m_inputmngr, m_engine->m_window);
	m_player->Initialize();
	
	return true;
};

void GameObjectManager::Update(float deltatime)
{
	m_engine->m_view->setCenter(m_player->GetPosition());
	m_engine->m_view->setRotation(m_player->GetRotation() - 90);
	m_engine->m_view->setCenter(m_player->GetAnchor());
	m_engine->m_window->setView(*m_engine->m_view);

	m_player->Update(deltatime);
	m_player->WallCollision(m_walls);

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

	m_player->Draw();
	
};

void GameObjectManager::Clear()
{
	m_engine = nullptr;
};