#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Humanoid.h"
#include "PlayerControls.h"
#include "Wall.h"
#include "Ground.h"
#include "WallCorner.h"
#include "WallEdge.h"
#include "TWall.h"
#include "Solid.h"
#include "Level.h"
#include "Zombie.h"

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
	m_level->CreateLevel(m_walls);

	m_goal.setPosition(120*32, 102*32);
	m_goal.setSize(sf::Vector2f(64, 64));
	m_goal.setFillColor(sf::Color::Green);
	//BigGround
	m_grounds.push_back(new Ground(sf::Vector2i(140*32, 118*32), sf::Vector2f(0, 0)));

	//bool t_connectedsides[4] = {false, true, false, true};
	////House 1
	//m_walls.push_back(new Wall(sf::Vector2f(32,0), sf::Vector2f(64*4,32), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*5,0), sf::Vector2f(64,32), t_connectedsides));
	//m_walls.push_back(new TWall(sf::Vector2f(32 + 64*4,0), sf::Vector2f(32, 32), 0));
	//m_walls.push_back(new WallCorner(sf::Vector2f(0,0), sf::Vector2f(32, 32), 0));
	//t_connectedsides[0] = true;
	//t_connectedsides[1] = false;
	//t_connectedsides[2] = true;
	//t_connectedsides[3] = false;
	//m_walls.push_back(new Wall(sf::Vector2f(32 + 64*4,32), sf::Vector2f(32,64), t_connectedsides));
	//m_walls.push_back(new WallEdge(sf::Vector2f(32 + 64*4, 64 + 32), sf::Vector2f(32, 32), 2));
	//m_walls.push_back(new Wall(sf::Vector2f(0,32), sf::Vector2f(32,4*64), t_connectedsides));
	//m_walls.push_back(new WallCorner(sf::Vector2f(0,4*64 + 32), sf::Vector2f(32, 32), 3));
	//t_connectedsides[0] = false;
	//t_connectedsides[1] = true;
	//t_connectedsides[2] = false;
	//t_connectedsides[3] = true;
	//
	//m_walls.push_back(new Wall(sf::Vector2f(32, 4*64 + 32), sf::Vector2f(5*64-32, 32), t_connectedsides));
	//m_walls.push_back(new WallEdge(sf::Vector2f(5*64,4*64 + 32), sf::Vector2f(32, 32), 1));
	//t_connectedsides[3] = false;
	//m_walls.push_back(new Wall(sf::Vector2f(32 + 6*64, 4*64 + 32), sf::Vector2f(5*64 + 32, 32), t_connectedsides));
	//t_connectedsides[0] = true;
	//m_walls.push_back(new Wall(sf::Vector2f(11*64 + 32, 32), sf::Vector2f(32, 64), t_connectedsides));
	//t_connectedsides[0] = false;
	//m_walls.push_back(new Wall(sf::Vector2f(11*64 + 32, 32 + 64*2), sf::Vector2f(32, 64 * 2), t_connectedsides));
	////m_walls.push_back(new Wall(sf::Vector2f(9*64, 32), sf::Vector2f(32, 3*64), t_connectedsides));

	////Trees
	//m_walls.push_back(new Wall(sf::Vector2f(64*17,0), sf::Vector2f(64,64), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*25,0), sf::Vector2f(64,64), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*17,4*64), sf::Vector2f(64,64), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*25,4*64), sf::Vector2f(64,64), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*21,2*64), sf::Vector2f(64,64), t_connectedsides));

	////House 2
	//m_walls.push_back(new Wall(sf::Vector2f(64*16,8*64), sf::Vector2f(32 + 3*64,32), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*20 + 32,8*64), sf::Vector2f(32 + 64,32), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*16,8*64 + 32), sf::Vector2f(32, 3*64), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*16,12*64 + 32), sf::Vector2f(32, 6*64 + 32), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*21 + 32,8*64 + 32), sf::Vector2f(32, 10*64 + 32), t_connectedsides));
	//m_walls.push_back(new Wall(sf::Vector2f(64*16 + 32,18*64 + 32), sf::Vector2f(5*64, 32), t_connectedsides));



	m_player = new Humanoid(new PlayerControls(m_engine->m_inputmngr, m_engine->m_window));

	m_leftviewlimit.setSize(sf::Vector2f(1920, 1080));
	m_leftviewlimit.setOrigin(1920, 0);
	m_leftviewlimit.setRotation(-200 + m_player->GetRotation());
	m_leftviewlimit.setFillColor(sf::Color::White);
	m_leftviewlimit.setPosition(m_player->GetPosition());

	m_rightviewlimit.setSize(sf::Vector2f(1920, 1080));
	m_rightviewlimit.setFillColor(sf::Color::White);
	m_rightviewlimit.setRotation(+160 + m_player->GetRotation());
	m_rightviewlimit.setPosition(m_player->GetPosition());

	m_backviewlimit.setSize(sf::Vector2f(1920, 1080));
	m_leftviewlimit.setOrigin(1920/2, 0);
	m_backviewlimit.setFillColor(sf::Color::White);
	m_backviewlimit.setRotation(m_player->GetRotation());
	m_backviewlimit.setPosition(m_player->GetPosition());

	m_zombies = new Zombie(m_player->GetPosition() + sf::Vector2f(-500*sin((m_player->GetRotation()+90)), -500*cos((m_player->GetRotation()+90))));
	
	return true;
};

void GameObjectManager::Update(float deltatime)
{
	m_player->Update(deltatime);
	m_player->WallCollision(m_walls);


	m_zombies->Update(deltatime, m_player->GetPosition());
	m_player->ZombieCollision(m_zombies->GetBody());
	m_zombies->CheckIfHit(*m_player);

	m_engine->m_view->setCenter(m_player->GetPosition());
	m_engine->m_view->setRotation(m_player->GetRotation() - 90);
	m_engine->m_view->setCenter(m_player->GetCameraAnchor());
	m_engine->m_window->setView(*m_engine->m_view);

	m_leftviewlimit.setRotation(-80 + m_player->GetRotation());
	m_leftviewlimit.setPosition(m_player->GetPosition());

	m_rightviewlimit.setRotation(-100 + m_player->GetRotation());
	m_rightviewlimit.setPosition(m_player->GetPosition());

	m_backviewlimit.setRotation(m_player->GetRotation());
	m_backviewlimit.setPosition(m_player->GetPosition());

	for(int i = 0; i<m_walls.size(); i++)
	{
		float t_deltaX = m_player->GetPosition().x-m_walls.at(i)->GetWall().getPosition().x;
		float t_deltaY = m_player->GetPosition().y-m_walls.at(i)->GetWall().getPosition().y;
		float dist = sqrtf((t_deltaX*t_deltaX)+(t_deltaY*t_deltaY));
		if(dist<1920)
		{
			m_walls.at(i)->Update(m_player);
		}
	}

	m_player->GroundCollision(m_grounds);

	if(!m_player->GetExistance()) m_engine->m_statemanager.SetNextState("GameOver");
	if(m_goal.getGlobalBounds().contains(m_player->GetPosition()))
	{
		m_engine->m_statemanager.SetNextState("VictoryState");
	}
};

void GameObjectManager::Draw()
{
	for(int i = 0; i<m_grounds.size(); i++)
	{
		m_grounds.at(i)->Draw(*m_engine->m_window);
	}

		m_zombies->Draw(*m_engine->m_window);

	for(int i = 0; i<m_walls.size(); i++)
	{
		float t_deltaX = m_player->GetPosition().x-m_walls.at(i)->GetWall().getPosition().x;
		float t_deltaY = m_player->GetPosition().y-m_walls.at(i)->GetWall().getPosition().y;
		float dist = sqrtf((t_deltaX*t_deltaX)+(t_deltaY*t_deltaY));
		if(dist<1920)
		{
			m_walls.at(i)->Draw(*m_engine->m_window);
		}
	}
	m_engine->m_window->draw(m_goal);
	m_engine->m_window->draw(m_leftviewlimit);
	m_engine->m_window->draw(m_rightviewlimit);
	m_engine->m_window->draw(m_backviewlimit);
	m_player->Draw(*m_engine->m_window);
	for(int i = 0; i<m_walls.size(); i++)
	{
		float t_deltaX = m_player->GetPosition().x-m_walls.at(i)->GetWall().getPosition().x;
		float t_deltaY = m_player->GetPosition().y-m_walls.at(i)->GetWall().getPosition().y;
		float dist = sqrtf((t_deltaX*t_deltaX)+(t_deltaY*t_deltaY));
		if(dist<1920)
		{
			m_walls.at(i)->DrawShadows(*m_engine->m_window);
		}
	}

};

void GameObjectManager::Clear()
{
	delete m_player;
	m_player = nullptr;
	delete m_zombies;
	m_zombies = nullptr;
	for (auto it = m_walls.begin();it != m_walls.end(); it++)
	{
		if(*it != nullptr) {
			delete *it;
		}
	}
	m_walls.clear();
};