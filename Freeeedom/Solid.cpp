#include "stdafx.h"
#include "Solid.h"


Solid::Solid(void)
{
}

void Solid::GetShadows(sf::ConvexShape p_shadows[4], sf::RectangleShape p_shadowaim)
{
	p_shadows = m_shadow;
	p_shadowaim = m_shadowaim;
}

void Solid::SetSize(sf::Vector2f p_increasement)
{
	m_wall.setSize(m_wall.getSize() + p_increasement);
	m_shadowaim.setSize(sf::Vector2f(m_wall.getSize().x*50, m_wall.getSize().y*50));
}