#include "stdafx.h"
#include "Ground.h"


Ground::Ground(sf::Vector2i p_sizetimes32, sf::Vector2f p_position)
{
	m_ground.setSize(sf::Vector2f(p_sizetimes32.x*32, p_sizetimes32.y*32));
	m_ground.setPosition(p_position);
	m_ground.setFillColor(sf::Color(255/2, 255/2, 255/2, 255));
}

void Ground::Draw(sf::RenderWindow& p_renderer)
{
	p_renderer.draw(m_ground);
}

sf::RectangleShape Ground::GetSquare()
{
	return m_ground;
}

Ground::~Ground(void)
{
}
