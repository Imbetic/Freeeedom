#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "PlayerObject.h"

GameObjectManager::GameObjectManager(Engine* engine)
{
	m_engine = engine;
}


GameObjectManager::~GameObjectManager(void)
{
}

bool GameObjectManager::Initialize()
{
	sf::RectangleShape* rectangle = new sf::RectangleShape; 
	sf::RectangleShape* rect = new sf::RectangleShape; 
		
	rectangle->setSize(sf::Vector2f(20, 1000));
	rectangle->setFillColor(sf::Color::Red);
	rectangle->setPosition(sf::Vector2f(500, 500));
	m_rectangles.push_back(rectangle);
	rect->setSize(sf::Vector2f(1000, 20));
	rect->setFillColor(sf::Color::Red);
	rect->setPosition(sf::Vector2f(500, 500));
	m_rectangles.push_back(rect);
	m_gameobjects.push_back(new PlayerObject(m_engine->m_inputmngr, m_engine->m_window));
	m_gameobjects.at(0)->Initialize();
	return true;
};

void GameObjectManager::Update(float deltatime)
{
	m_engine->m_view->setCenter(m_gameobjects.at(0)->GetPosition());
	m_engine->m_view->setRotation(m_gameobjects.at(0)->GetRotation() - 90);
	m_engine->m_view->setCenter(m_gameobjects.at(0)->GetAnchor());
	m_engine->m_window->setView(*m_engine->m_view);
	for(int i = 0; i<m_gameobjects.size(); i++)
	{
		//SetPlayer
		//SetVisible
		//SetPositions
		//SetCollisions
		m_gameobjects.at(i)->Update(deltatime);
		m_gameobjects.at(i)->WallCollision(m_rectangles);

		if(m_gameobjects.at(i)->GetExistance() == false){
			delete m_gameobjects.at(i);
			//Erase them too
		};
	}
};

void GameObjectManager::Draw()
{
	for(int i = 0; i<m_gameobjects.size(); i++)
	{
		m_gameobjects.at(i)->Draw();
	}
	for(int i = 0; i<m_rectangles.size(); i++)
	{
		m_engine->m_window->draw(*m_rectangles.at(i));
	}
	
};

void GameObjectManager::Clear()
{
	m_engine = nullptr;
};