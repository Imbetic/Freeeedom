#include "stdafx.h"
//#include "PlayerObject.h"
//#include "InputManager.h"
//#include <iostream>
//
//PlayerObject::PlayerObject(InputManager* p_input, sf::RenderWindow* p_window)
//{
//	m_input = p_input;
//	m_window = p_window;
//
//	m_acceleration = 1500;
//	m_friction = 10;
//	m_radius = 25;
//	m_position = sf::Vector2f(100, 100);
//	m_body.setPosition(m_position);
//	m_body.setRadius(m_radius);
//	m_body.setOrigin(m_radius, m_radius);
//	m_body.setFillColor(sf::Color::Black);
//	m_previousmouspos = 0;
//	m_rotationspeed = 12;
//	m_viewdistance = 250;
//	m_released = false;
//}
//
//void PlayerObject::Update(float deltatime)
//{
//	m_deltamouse = sf::Mouse::getPosition(*m_window).x - m_previousmouspos;
//	sf::Mouse::setPosition(sf::Vector2i(1280/2, 720/2), *m_window);
//	m_rotation+= m_deltamouse*deltatime*m_rotationspeed;
//	m_body.setRotation(m_rotation);
//
//	if(m_input->IsDownK(sf::Keyboard::W) || m_input->IsDownK(sf::Keyboard::S) || m_input->IsDownK(sf::Keyboard::A) || m_input->IsDownK(sf::Keyboard::D)){
//
//		const float pi = 3.141592654f;
//
//		if(m_input->IsDownK(sf::Keyboard::LShift)&&m_input->IsDownK(sf::Keyboard::W))
//		{
//			m_acceleration = 3000;
//		}
//		else m_acceleration = 1500;
//
//		float accY=0;
//		float accX=0;
//		if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::D)){}
//		else if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::A))
//		{
//			accX=-cos((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
//			accY=-sin((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
//		}
//		else if(m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::D))
//		{
//			accX=cos(m_rotation*pi/180) * m_acceleration  * deltatime;
//			accY=sin(m_rotation*pi/180) * m_acceleration  * deltatime;
//		}
//		else if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::D) && m_input->IsDownK(sf::Keyboard::A))
//		{
//			accX=-cos(m_rotation*pi/180) * m_acceleration  * deltatime;
//			accY=-sin(m_rotation*pi/180) * m_acceleration  * deltatime;
//		}
//		else if(m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::D))
//		{
//			accX=-cos((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
//			accY=-sin((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
//		}
//		else{
//			if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::S)){}
//			else if(m_input->IsDownK(sf::Keyboard::W))
//			{
//				accX=-cos(m_rotation*pi/180) * m_acceleration  * deltatime;
//				accY=-sin(m_rotation*pi/180) * m_acceleration  * deltatime;
//			}
//			else if(m_input->IsDownK(sf::Keyboard::S))
//			{
//				accX=cos(m_rotation*pi/180) * m_acceleration  * deltatime;
//				accY=sin(m_rotation*pi/180) * m_acceleration  * deltatime;
//			};
//
//			if(m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::D)){}
//			else if(m_input->IsDownK(sf::Keyboard::A))
//			{
//				accX=-cos((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
//				accY=-sin((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
//			}
//			else if(m_input->IsDownK(sf::Keyboard::D)){
//				accX=-cos((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
//				accY=-sin((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
//			};
//
//			if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::D))
//			{
//				accX=-cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
//				accY=-sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
//			}
//
//			else if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::A))
//			{
//				accX=-cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
//				accY=-sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
//			}
//
//			else if(m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::S))
//			{
//				accX=cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
//				accY=sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
//			}
//
//			else if(m_input->IsDownK(sf::Keyboard::D) && m_input->IsDownK(sf::Keyboard::S))
//			{
//				accX=cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
//				accY=sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
//			}
//		}
//		m_velocity += sf::Vector2f(accX, accY);
//	};
//
//	m_position += m_velocity * deltatime;
//	m_velocity.x-=m_velocity.x*m_friction*deltatime;
//	m_velocity.y-=m_velocity.y*m_friction*deltatime;
//	m_body.setPosition(m_position);
//
//
//
//	if(m_input->IsDownOnce(MB_LEFT) && !m_released)
//	{
//		m_loading = true;
//	}
//
//	if(m_loading)
//	{ 
//		//§§§m_weapon->Load(float deltatime)
//	};
//
//	if(!m_input->IsDown(MB_LEFT))
//	{
//		m_loading = false;
//		m_released = true;
//	}
//
//	m_cameraanchor = sf::Vector2f(m_position.x+m_viewdistance*-cos(m_rotation*pi/180), m_position.y+m_viewdistance*-sin(m_rotation*pi/180));
//	m_previousmouspos = sf::Mouse::getPosition(*m_window).x;
//};
//
//sf::Vector2f PlayerObject::GetAnchor()
//{
//	return m_cameraanchor;
//}
//
//void PlayerObject::Attack()
//{
//	/*if(m_weapon->Load(bool loading))
//	{
//
//	}*/
//};
//
//PlayerObject::~PlayerObject(void)
//{
//
//}
//
//void PlayerObject::Draw()
//{
//	m_window->draw(m_body);
//};
//
//float PlayerObject::GetStrength()
//{
//	return m_strength;
//};
//
//float PlayerObject::GetDeltaMouse()
//{
//	return m_deltamouse;
//};