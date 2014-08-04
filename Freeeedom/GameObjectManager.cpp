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
	m_engine = nullptr;
}

bool GameObjectManager::Initialize()
{
	//House 1
	m_walls.push_back(new Wall(sf::Vector2f(0,0), sf::Vector2f(64*12,32)));
	m_walls.push_back(new Wall(sf::Vector2f(0,32), sf::Vector2f(32,4*64 + 32)));
	m_walls.push_back(new Wall(sf::Vector2f(32, 4*64 + 32), sf::Vector2f(5*64, 32)));
	m_walls.push_back(new Wall(sf::Vector2f(32 + 64*2, 32+64), sf::Vector2f(32, 3*64)));
	m_walls.push_back(new Wall(sf::Vector2f(32 + 6*64, 4*64 + 32), sf::Vector2f(5*64 + 32, 32)));
	m_walls.push_back(new Wall(sf::Vector2f(11*64 + 32, 32), sf::Vector2f(32, 64)));
	m_walls.push_back(new Wall(sf::Vector2f(11*64 + 32, 32 + 64*2), sf::Vector2f(32, 64 * 2)));
	m_walls.push_back(new Wall(sf::Vector2f(9*64, 32), sf::Vector2f(32, 3*64)));

	//Trees
	m_walls.push_back(new Wall(sf::Vector2f(64*17,0), sf::Vector2f(64,64)));
	m_walls.push_back(new Wall(sf::Vector2f(64*25,0), sf::Vector2f(64,64)));
	m_walls.push_back(new Wall(sf::Vector2f(64*17,4*64), sf::Vector2f(64,64)));
	m_walls.push_back(new Wall(sf::Vector2f(64*25,4*64), sf::Vector2f(64,64)));
	m_walls.push_back(new Wall(sf::Vector2f(64*21,2*64), sf::Vector2f(64,64)));

	//House 2
	m_walls.push_back(new Wall(sf::Vector2f(64*16,8*64), sf::Vector2f(32 + 3*64,32)));
	m_walls.push_back(new Wall(sf::Vector2f(64*20 + 32,8*64), sf::Vector2f(32 + 64,32)));
	m_walls.push_back(new Wall(sf::Vector2f(64*16,8*64 + 32), sf::Vector2f(32, 3*64)));
	m_walls.push_back(new Wall(sf::Vector2f(64*16,12*64 + 32), sf::Vector2f(32, 6*64 + 32)));
	m_walls.push_back(new Wall(sf::Vector2f(64*21 + 32,8*64 + 32), sf::Vector2f(32, 10*64 + 32)));
	m_walls.push_back(new Wall(sf::Vector2f(64*16 + 32,18*64 + 32), sf::Vector2f(5*64, 32)));



	m_player = new Humanoid(new PlayerControls(m_engine->m_inputmngr, m_engine->m_window));

	return true;
};

void GameObjectManager::Update(float deltatime)
{

	std::cout<< deltatime << std::endl;
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

	if(!m_player->GetExistance()) m_engine->m_statemanager.SetNextState("GameOver");

};

void GameObjectManager::Draw()
{
	m_player->Draw(m_engine->m_window);
	for(int i = 0; i<m_walls.size(); i++)
	{
		m_walls.at(i)->DrawShadows(m_engine->m_window);
	}
	for(int i = 0; i<m_walls.size(); i++)
	{
		m_walls.at(i)->Draw(m_engine->m_window);
	}



};

void GameObjectManager::Clear()
{
	delete m_player;
	m_player = nullptr;
	for (auto it = m_walls.begin();it != m_walls.end(); it++)
	{
		if(*it != nullptr) {
			delete *it;
		}
	}
	m_walls.clear();
};