#include "stdafx.h"
#include "MeleeWeapon.h"


MeleeWeapon::MeleeWeapon(float p_handlelength, float p_bodysize, float p_weight)
{
	m_handle.setSize(sf::Vector2f(6, p_handlelength));
	m_handle.setOrigin(3, 0);
	m_handle.setFillColor(sf::Color::Color(255/4, 255/4, 255/4, 255));
	m_body.setFillColor(sf::Color::Color(255/4, 255/4, 255/4, 255));
	m_body.setRadius(p_bodysize);
	m_body.setOrigin(p_bodysize, p_bodysize);
	m_weight = p_weight;
}

void MeleeWeapon::Update(float angle, sf::Vector2f p_position)
{
	m_handle.setPosition(p_position);
	m_handle.setRotation(angle);
	m_body.setPosition(sf::Vector2f(p_position.x - (m_handle.getSize().y * sinf(angle*3.141592654f/180)), p_position.y + (m_handle.getSize().y * cosf(angle*3.141592654f/180))));
}

float MeleeWeapon::GetWeight()
{
	return m_weight;
}

sf::CircleShape MeleeWeapon::GetBody()
{
	return m_body;
}

sf::RectangleShape MeleeWeapon::GetHandle()
{
	return m_handle;
}

MeleeWeapon::~MeleeWeapon(void)
{
}
