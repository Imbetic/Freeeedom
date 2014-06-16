#include "stdafx.h"
#include "PlayerObject.h"
#include "InputManager.h"
#include "WeaponObject.h"
#include <iostream>

PlayerObject::PlayerObject(InputManager* p_input, sf::RenderWindow* window)
{
	m_window = window;
	m_input = p_input;
}

bool PlayerObject::Initialize()
{
	m_acceleration = 0.2;
	m_friction = 0.99;
	m_radius = 25;
	m_position = sf::Vector2f(0, 100);
	m_previousposition = m_position;
	m_body.setPosition(m_position);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Black);
	m_previousmouspos = 0;
	m_rotationspeed = 3;
	m_viewdistance = 250;
	for(int i = 0; i < 4; i++){
		m_numbercount[i]=i;
	}
	m_numbercount[5]=0;
	m_released = false;
	m_weapon = new WeaponObject(this, m_input);
	return true;
};
void PlayerObject::Update(float deltatime)
{
	m_deltamouse = 0;
	m_previousposition = m_position;

	float accY=0;
	float accX=0;
	const float pi = 3.141592654f;

	if(m_input->IsDownK(sf::Keyboard::LShift)&&m_input->IsDownK(sf::Keyboard::W))
	{
		m_acceleration = 0.4;
	}
	else m_acceleration = 0.2;

	if(sqrt((m_velocity.x*m_velocity.x)+(m_velocity.y*m_velocity.y)) < 0.9) m_friction = 0.99;

	//float delta_X = m_position.x-sf::Mouse::getPosition(*m_window).x;
	//float delta_Y = m_position.y-sf::Mouse::getPosition(*m_window).y;
	//float dist = sqrt(delta_X*delta_X+delta_Y*delta_Y);
	m_deltamouse = sf::Mouse::getPosition(*m_window).x - m_previousmouspos;
	sf::Mouse::setPosition(sf::Vector2i(1280/2, 720/2), *m_window);
	//m_rotation=(atan2(delta_Y/dist, delta_X/dist))*(180/pi);
	m_rotation+= m_deltamouse*deltatime*m_rotationspeed;

	if(m_input->IsDownK(sf::Keyboard::W) || m_input->IsDownK(sf::Keyboard::S) || m_input->IsDownK(sf::Keyboard::A) || m_input->IsDownK(sf::Keyboard::D)){
		if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::D)){}
		else if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::A))
		{
			accX=-cos((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
			accY=-sin((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
		}
		else if(m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::D))
		{
			accX=cos(m_rotation*pi/180) * m_acceleration  * deltatime;
			accY=sin(m_rotation*pi/180) * m_acceleration  * deltatime;
		}
		else if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::D) && m_input->IsDownK(sf::Keyboard::A))
		{
			accX=-cos(m_rotation*pi/180) * m_acceleration  * deltatime;
			accY=-sin(m_rotation*pi/180) * m_acceleration  * deltatime;
		}
		else if(m_input->IsDownK(sf::Keyboard::S) && m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::D))
		{
			accX=-cos((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
			accY=-sin((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
		}
		else{
			if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::S)){}
			else if(m_input->IsDownK(sf::Keyboard::W))
			{
				accX=-cos(m_rotation*pi/180) * m_acceleration  * deltatime;
				accY=-sin(m_rotation*pi/180) * m_acceleration  * deltatime;
			}
			else if(m_input->IsDownK(sf::Keyboard::S))
			{
				accX=cos(m_rotation*pi/180) * m_acceleration  * deltatime;
				accY=sin(m_rotation*pi/180) * m_acceleration  * deltatime;
			};

			if(m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::D)){}
			else if(m_input->IsDownK(sf::Keyboard::A))
			{
				accX=-cos((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
			}
			else if(m_input->IsDownK(sf::Keyboard::D)){
				accX=-cos((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
			};

			if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::D))
			{
				accX=-cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
			}

			else if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::A))
			{
				accX=-cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
			}

			else if(m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::S))
			{
				accX=cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
				accY=sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
			}

			else if(m_input->IsDownK(sf::Keyboard::D) && m_input->IsDownK(sf::Keyboard::S))
			{
				accX=cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
				accY=sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
			}
		}
	};


	m_velocity += sf::Vector2f(accX, accY);
	m_position += m_velocity;
	m_velocity.x*=m_friction;
	m_velocity.y*=m_friction;
	m_body.setRotation(m_rotation);
	m_body.setPosition(m_position);

	if(m_input->IsDownOnce(MB_LEFT) && !m_released)
	{
		m_weapon->Initialize();
		m_loading = true;
	}
	
	if(m_loading)
	{ 
		//§§§m_weapon->Load(float deltatime)
	};

	if(!m_input->IsDown(MB_LEFT))
	{
		m_loading = false;
		m_released = true;
	}

	if(m_released)
	{
		m_weapon->Update(deltatime);
		m_weapon->Draw();
		/*if(m_weapon->DoneSwinging())
		{
			m_weapon->Reset();
			m_released = false;
		}*/
	}


	m_cameraanchor = sf::Vector2f(m_position.x+m_viewdistance*-cos(m_rotation*pi/180), m_position.y+m_viewdistance*-sin(m_rotation*pi/180));
	m_previousmouspos = sf::Mouse::getPosition(*m_window).x;
};

void PlayerObject::Hit(std::vector<sf::CircleShape*> circles)
{
	for(int i = 0; i < circles.size(); i++)
	{
		float dX = m_position.x - circles.at(i)->getPosition().x;
		float dY = m_position.y - circles.at(i)->getPosition().y;
		float dist = sqrt((dX*dX) + (dY*dY));
		if(dist == 0) dist = 0.1;
		if(dist<m_radius + circles.at(i)->getRadius())
		{
			float overlapdist = m_radius + circles.at(i)->getRadius() - dist;
			float x = overlapdist * dX /dist;
			float y = overlapdist * dY /dist;
			m_position += sf::Vector2f(x, y);
			m_velocity += sf::Vector2f(2*dX/dist, 2*dY/dist);
			m_friction = 0.999;
		};
	}
};

void PlayerObject::WallCollision(std::vector<sf::RectangleShape*> rectangles)
{
	bool xcollision = false;
	bool ycollision = false;
	for(int i = 0; i<rectangles.size(); i++)
	{
		sf::Vector2f line[4];

		if(rectangles.at(i)->getPointCount() == 4)
		{
			for(int j = 0; j < 4; j++)
			{
				if(rectangles.at(i)->getRotation() == 0){
					float dX = m_position.x - (rectangles.at(i)->getPoint(j).x + rectangles.at(i)->getPosition().x);
					float dY = m_position.y - (rectangles.at(i)->getPoint(j).y + rectangles.at(i)->getPosition().x);
					float dist = sqrt((dX*dX) + (dY*dY));
					if(dist == 0) dist = 0.1;
					if(dist<m_radius)
					{
						float overlapdist = m_radius - dist;
						float x = overlapdist * dX /dist;
						float y = overlapdist * dY /dist;
						m_position += sf::Vector2f(x, y);
						m_body.setPosition(m_position);
						//if(sqrt((m_actualvelocity.x*m_actualvelocity.x) + (m_actualvelocity.y*m_actualvelocity.y)) > 0.2) std::cout << "FATAL COLLISION" << std::endl;
						m_actualvelocity.x = 0;
						m_actualvelocity.y = 0;

					};

				}

				/*float deltaY = rectangles.at(i)->getPoint(j).y - rectangles.at(i)->getPoint(j+1).y;
				float deltaX = rectangles.at(i)->getPoint(j).x - rectangles.at(i)->getPoint(j+1).x;
				if(deltaX == 0 || deltaY == 0)
				{
				if(rectangles.at(i)->getGlobalBounds().intersects(m_body.getGlobalBounds()))
				{
				if(m_position.x < rectangles.at(i)->getPosition().x)
				{
				float overlapX = rectangles.at(i)->getPosition().x - m_position.x;
				}
				}
				}
				else
				{
				float k = deltaY/deltaX;
				float m = rectangles.at(i)->getPoint(j).y - k*rectangles.at(i)->getPoint(j).x;
				line[j] = sf::Vector2f(k ,m);
				}*/

			}
			if(m_position.x + m_radius > rectangles.at(i)->getPosition().x 
				&& m_position.x + m_radius < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
				&& m_position.y < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
				&& m_position.y >  rectangles.at(i)->getPosition().y){

					if(m_actualvelocity.x > 0.9)  std::cout<< m_actualvelocity.x << "   FATAL COLLISION" << std::endl;
					m_position.x = rectangles.at(i)->getPosition().x - m_radius;
					m_body.setPosition(m_position);
					m_actualvelocity.x = m_previousposition.x - m_position.x;
					m_velocity.x = -m_actualvelocity.x;
					xcollision = true;

			}
			if(m_position.x - m_radius > rectangles.at(i)->getPosition().x 
				&& m_position.x - m_radius < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
				&& m_position.y < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
				&& m_position.y >  rectangles.at(i)->getPosition().y){

					if(m_actualvelocity.x < -0.9)  std::cout<< m_actualvelocity.x << "   FATAL COLLISION" << std::endl;
					m_position.x = rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x + m_radius;
					m_body.setPosition(m_position);
					m_actualvelocity.x = 0;
					m_velocity.x = 0;
					xcollision = true;

			}
			if(m_position.y + m_radius > rectangles.at(i)->getPosition().y 
				&& m_position.y + m_radius < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
				&& m_position.x < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
				&& m_position.x >  rectangles.at(i)->getPosition().x){

					if(m_actualvelocity.y > 0.9)  std::cout<< m_actualvelocity.y << "   FATAL COLLISION" << std::endl;
					m_position.y = rectangles.at(i)->getPosition().y - m_radius;
					m_body.setPosition(m_position);
					m_actualvelocity.y = 0;
					m_velocity.y = 0;
					ycollision = true;

			}
			if(m_position.y - m_radius > rectangles.at(i)->getPosition().y 
				&& m_position.y - m_radius < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
				&& m_position.x < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
				&& m_position.x >  rectangles.at(i)->getPosition().x){

					if(m_actualvelocity.y < -0.9)  std::cout<< m_actualvelocity.y << "   FATAL COLLISION" << std::endl;
					m_position.y = rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y + m_radius;
					m_body.setPosition(m_position);
					m_actualvelocity.y = 0;
					m_velocity.y = 0;
					ycollision = true;
			}
			if(!ycollision && !xcollision)
			{
				m_actualvelocity = m_velocity;
			}
			else if(xcollision)
			{
				m_actualvelocity.x = m_previousposition.x - m_position.x;
			}
			else if(ycollision)
			{
				m_actualvelocity.y = m_previousposition.y - m_position.y;
			}
		}

	}
}

void PlayerObject::Attack()
{
	/*if(m_weapon->Load(bool loading))
	{
	
	}*/
};

PlayerObject::~PlayerObject(void)
{

}

void PlayerObject::Draw()
{
	m_window->draw(m_body);
};

Weapon PlayerObject::GetWeapon()
{
	return m_weaponstats;
};

float PlayerObject::GetStrength()
{
	return m_strength;
};

float PlayerObject::GetDeltaMouse()
{
	return m_deltamouse;
};

sf::Vector2f PlayerObject::GetSocket(int i)
{
	if(i == 1)
	{
		return m_socketone;
	}
	else return m_sockettwo;
}