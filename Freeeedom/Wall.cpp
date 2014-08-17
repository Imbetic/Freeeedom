#include "stdafx.h"
#include "Wall.h"
#include "GameObject.h"


Wall::Wall(sf::Vector2f p_position, sf::Vector2f p_size, bool p_connectedsides[4])
{
	for(int i = 0; i<4; i++)
	{
		m_connectedsides[i] = p_connectedsides[i];
	}
	m_wall.setSize(p_size);
	m_shadowaim.setSize(sf::Vector2f(p_size.x*50, p_size.y*50));
	m_wall.setPosition(p_position);
	m_wall.setFillColor(sf::Color::Color(255/4, 255/4, 255/4));
	m_shadowaim.setFillColor(sf::Color::White);

	for(int i = 0; i<4; i++)
	{
		m_shadow[i].setFillColor(sf::Color::White);
		m_shadow[i].setPointCount(4);
	}
}

void Wall::Update(GameObject* p_player)
{
	//If this object is inside the screen
	{
		float dY = p_player->GetPosition().y - m_wall.getPosition().y;
		float dX = p_player->GetPosition().x - m_wall.getPosition().x;

		m_playerposition = p_player->GetPosition();

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

void Wall::Draw(sf::RenderWindow& p_renderer)
{
	p_renderer.draw(m_wall);

}

void Wall::DrawShadows(sf::RenderWindow& p_renderer)
{
	p_renderer.draw(m_shadowaim);

	if(m_playerposition.x < m_wall.getPosition().x && m_playerposition.y < m_wall.getPosition().y)
	{
		m_shadowsides[0] = false;
		m_shadowsides[1] = true;
		m_shadowsides[2] = true;
		m_shadowsides[3] = false;
	}
	else if(m_playerposition.x > m_wall.getPosition().x + m_wall.getSize().x && m_playerposition.y > m_wall.getPosition().y + m_wall.getSize().y)
	{
		m_shadowsides[0] = true;
		m_shadowsides[1] = false;
		m_shadowsides[2] = false;
		m_shadowsides[3] = true;
	}
	else if(m_playerposition.x > m_wall.getPosition().x + m_wall.getSize().x && m_playerposition.y < m_wall.getPosition().y)
	{
		m_shadowsides[0] = false;
		m_shadowsides[1] = false;
		m_shadowsides[2] = true;
		m_shadowsides[3] = true;
	}
	else if(m_playerposition.x < m_wall.getPosition().x && m_playerposition.y > m_wall.getPosition().y + m_wall.getSize().y)
	{
		m_shadowsides[0] = true;
		m_shadowsides[1] = true;
		m_shadowsides[2] = false;
		m_shadowsides[3] = false;
	}
	else if(m_playerposition.x > m_wall.getPosition().x && m_playerposition.x < m_wall.getPosition().x + m_wall.getSize().x && m_playerposition.y < m_wall.getPosition().y)
	{
		m_shadowsides[0] = false;
		m_shadowsides[1] = true;
		m_shadowsides[2] = true;
		m_shadowsides[3] = true;
	}
	else if(m_playerposition.x > m_wall.getPosition().x && m_playerposition.x < m_wall.getPosition().x + m_wall.getSize().x && m_playerposition.y > m_wall.getPosition().y + m_wall.getSize().y)
	{
		m_shadowsides[0] = true;
		m_shadowsides[1] = true;
		m_shadowsides[2] = false;
		m_shadowsides[3] = true;
	}
	else if(m_playerposition.x < m_wall.getPosition().x && m_playerposition.y > m_wall.getPosition().y && m_playerposition.y < m_wall.getPosition().y + m_wall.getSize().y)
	{
		m_shadowsides[0] = true;
		m_shadowsides[1] = true;
		m_shadowsides[2] = true;
		m_shadowsides[3] = false;
	}
	else if(m_playerposition.x > m_wall.getPosition().x + m_wall.getSize().x && m_playerposition.y > m_wall.getPosition().y && m_playerposition.y < m_wall.getPosition().y + m_wall.getSize().y)
	{
		m_shadowsides[0] = true;
		m_shadowsides[1] = false;
		m_shadowsides[2] = true;
		m_shadowsides[3] = true;
	}

	for(int i = 0; i<4; i++)
	{
		if(!m_connectedsides[i])
		{
			if(m_shadowsides[i])
			{
				p_renderer.draw(m_shadow[i]);
			}
		}
	}
}

sf::RectangleShape Wall::GetWall()
{
	return m_wall;
}

Wall::~Wall(void)
{

}
