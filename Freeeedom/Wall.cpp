#include "stdafx.h"
#include "Wall.h"
#include "GameObject.h"


Wall::Wall(sf::Vector2f p_position, sf::Vector2f p_size)
{
	m_wall.setSize(p_size);
	m_shadowaim.setSize(sf::Vector2f(p_size.x*50, p_size.y*50));
	m_wall.setPosition(p_position);
	m_wall.setFillColor(sf::Color::Black);
	m_shadowaim.setFillColor(sf::Color::Color(255/2, 255/2, 255/2));

	for(int i = 0; i<4; i++)
	{
		m_shadow[i].setFillColor(sf::Color::Color(255/2, 255/2, 255/2));
		m_shadow[i].setPointCount(4);
	}
}

void Wall::Update(GameObject* p_player)
{
	//If this object is inside the screen
	{
		float dY = p_player->GetPosition().y - m_wall.getPosition().y;
		float dX = p_player->GetPosition().x - m_wall.getPosition().x;

		m_shadowaim.setPosition(sf::Vector2f((m_wall.getPosition().x - (dX*49)), (m_wall.getPosition().y - (dY*49))));
	}

	m_shadow[0].setPoint(0, sf::Vector2f(m_shadowaim.getPoint(0).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(0).y + m_shadowaim.getPosition().y));
	m_shadow[0].setPoint(1, sf::Vector2f(m_shadowaim.getPoint(1).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(1).y + m_shadowaim.getPosition().y));
	m_shadow[0].setPoint(2, sf::Vector2f(m_wall.getPoint(1).x + m_wall.getPosition().x, m_wall.getPoint(1).y + m_wall.getPosition().y));
	m_shadow[0].setPoint(3, sf::Vector2f(m_wall.getPoint(0).x + m_wall.getPosition().x, m_wall.getPoint(0).y + m_wall.getPosition().y));

	m_shadow[1].setPoint(0, sf::Vector2f(m_shadowaim.getPoint(1).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(1).y + m_shadowaim.getPosition().y));
	m_shadow[1].setPoint(1, sf::Vector2f(m_shadowaim.getPoint(2).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(2).y + m_shadowaim.getPosition().y));
	m_shadow[1].setPoint(2, sf::Vector2f(m_wall.getPoint(2).x + m_wall.getPosition().x, m_wall.getPoint(2).y + m_wall.getPosition().y));
	m_shadow[1].setPoint(3, sf::Vector2f(m_wall.getPoint(1).x + m_wall.getPosition().x, m_wall.getPoint(1).y + m_wall.getPosition().y));

	m_shadow[2].setPoint(0, sf::Vector2f(m_shadowaim.getPoint(2).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(2).y + m_shadowaim.getPosition().y));
	m_shadow[2].setPoint(1, sf::Vector2f(m_shadowaim.getPoint(3).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(3).y + m_shadowaim.getPosition().y));
	m_shadow[2].setPoint(2, sf::Vector2f(m_wall.getPoint(3).x + m_wall.getPosition().x, m_wall.getPoint(3).y + m_wall.getPosition().y));
	m_shadow[2].setPoint(3, sf::Vector2f(m_wall.getPoint(2).x + m_wall.getPosition().x, m_wall.getPoint(2).y + m_wall.getPosition().y));

	m_shadow[3].setPoint(0, sf::Vector2f(m_shadowaim.getPoint(3).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(3).y + m_shadowaim.getPosition().y));
	m_shadow[3].setPoint(1, sf::Vector2f(m_shadowaim.getPoint(0).x + m_shadowaim.getPosition().x, m_shadowaim.getPoint(0).y + m_shadowaim.getPosition().y));
	m_shadow[3].setPoint(2, sf::Vector2f(m_wall.getPoint(0).x + m_wall.getPosition().x, m_wall.getPoint(0).y + m_wall.getPosition().y));
	m_shadow[3].setPoint(3, sf::Vector2f(m_wall.getPoint(3).x + m_wall.getPosition().x, m_wall.getPoint(3).y + m_wall.getPosition().y));
}

void Wall::Draw(sf::RenderWindow* p_renderer)
{
	p_renderer->draw(m_wall);

}

void Wall::DrawShadows(sf::RenderWindow* p_renderer)
{
	p_renderer->draw(m_shadowaim);
	for(int i = 0; i<4; i++)
	{
		p_renderer->draw(m_shadow[i]);
	}
}

sf::RectangleShape Wall::GetWall()
{
	return m_wall;
}

Wall::~Wall(void)
{

}
