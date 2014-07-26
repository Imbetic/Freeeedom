#include "stdafx.h"
#include "PlayerControls.h"
#include "InputManager.h"


PlayerControls::PlayerControls(InputManager* p_input, sf::RenderWindow* p_window)
{
	m_window = p_window;
	m_input = p_input;
	m_rotationamount = 0;
	m_loadattack = false;
}

void PlayerControls::Update()
{
	m_rotationamount = 0;
	if(m_input->IsDownK(sf::Keyboard::W)) m_movement[0] = true;
	else m_movement[0] = false;
	if(m_input->IsDownK(sf::Keyboard::A)) m_movement[1] = true;
	else m_movement[1] = false;
	if(m_input->IsDownK(sf::Keyboard::S)) m_movement[2] = true;
	else m_movement[2] = false;
	if(m_input->IsDownK(sf::Keyboard::D)) m_movement[3] = true;
	else m_movement[3] = false;

	if(m_input->IsDownK(sf::Keyboard::LShift)) m_run = true;
	else m_run = false;

	if(m_input->IsDown(EMouseButton::MB_LEFT))
	{
		m_loadattack = true;
	}
	else m_loadattack = false;

	m_rotationamount = sf::Mouse::getPosition(*m_window).x - m_previousmouspos;
	sf::Mouse::setPosition(sf::Vector2i(1280/2, 720/2), *m_window);
	m_previousmouspos = sf::Mouse::getPosition(*m_window).x;
}

PlayerControls::~PlayerControls(void)
{
}
