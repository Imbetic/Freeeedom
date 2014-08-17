#include "stdafx.h"
#include "Zombie.h"
#include "Solid.h"
#include "Humanoid.h"

Zombie::Zombie(sf::Vector2f p_position)
{
	m_radius = 32;
	m_position = p_position;
	m_body.setPosition(m_position);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::White);
	m_existance = true;
}

void Zombie::Update(float deltatime, sf::Vector2f p_playerposition)
{
	float dX = m_position.x - p_playerposition.x;
	float dY = m_position.y - p_playerposition.y;
	float dist = sqrt((dX*dX)+(dY*dY));

	m_velocity = sf::Vector2f(150*(dX/dist), 150*(dY/dist));

	m_position -= m_velocity*deltatime;
	m_body.setPosition(m_position);
	m_previousplayervision = m_playervision;
}

void Zombie::CheckIfHit(Humanoid& p_player)
{
	if(p_player.SwingCheck())
	{
		float dX = p_player.GetWeaponHead().getPosition().x - m_position.x;
		float dY = p_player.GetWeaponHead().getPosition().y - m_position.y;
		float dist = sqrtf((dX*dX)+(dY*dY));
		if(dist < 32+p_player.GetWeaponHead().getRadius()) m_position = p_player.GetPosition() + sf::Vector2f(-800*sin((p_player.GetRotation()-90)*0.0174532925), 500*cos((p_player.GetRotation()-800)*0.0174532925));
	}
}

Zombie::~Zombie(void)
{
}
