#include "stdafx.h"
#include "PlayerObject.h"
#include "InputManager.h"
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
	m_radius = 50;
	m_position = sf::Vector2f(500, 500);
	m_body.setPosition(m_position);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Green);
	m_previousmouspos = 0;
	m_rotationspeed = 3;
	m_viewdistance = 250;
	for(int i = 0; i < 4; i++){
		m_numbercount[i]=i;
	}
	m_numbercount[5]=0;
	return true;
};
void PlayerObject::Update(float deltatime)
{
	float accY=0;
	float accX=0;
	const float pi = 3.141592654f;

	if(m_input->IsDownK(sf::Keyboard::LShift)&&m_input->IsDownK(sf::Keyboard::W))
	{
		m_acceleration = 0.4;
	}
	else m_acceleration = 0.2;

	//float delta_X = m_position.x-sf::Mouse::getPosition(*m_window).x;
	//float delta_Y = m_position.y-sf::Mouse::getPosition(*m_window).y;
	//float dist = sqrt(delta_X*delta_X+delta_Y*delta_Y);
	float deltamouse = sf::Mouse::getPosition(*m_window).x - m_previousmouspos;
	sf::Mouse::setPosition(sf::Vector2i(1280/2, 720/2), *m_window);
	//m_rotation=(atan2(delta_Y/dist, delta_X/dist))*(180/pi);
	m_rotation+= deltamouse*deltatime*m_rotationspeed;

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

			if(m_input->IsDownK(sf::Keyboard::W) && m_input->IsDownK(sf::Keyboard::A))
			{
				accX=-cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
			}

			if(m_input->IsDownK(sf::Keyboard::A) && m_input->IsDownK(sf::Keyboard::S))
			{
				accX=cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
				accY=sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
			}

			if(m_input->IsDownK(sf::Keyboard::D) && m_input->IsDownK(sf::Keyboard::S))
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
	m_cameraanchor = sf::Vector2f(m_position.x+m_viewdistance*-cos(m_rotation*pi/180), m_position.y+m_viewdistance*-sin(m_rotation*pi/180));
	m_previousmouspos = sf::Mouse::getPosition(*m_window).x;
};
void PlayerObject::WallCollision(std::vector<sf::RectangleShape*> rectangles)
{
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
					if(dist<=m_radius)
					{
						float overlapdist = m_radius - dist;
						float x = overlapdist * dX /dist;
						float y = overlapdist * dY /dist;
						m_position += sf::Vector2f(x, y);
					};
					if(m_position.x + m_radius > rectangles.at(i)->getPosition().x 
						&& m_position.x + m_radius < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
						&& m_position.y < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
						&& m_position.y >  rectangles.at(i)->getPosition().y){

							m_position.x = rectangles.at(i)->getPosition().x - m_radius;

					}
					if(m_position.x - m_radius > rectangles.at(i)->getPosition().x 
						&& m_position.x - m_radius < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
						&& m_position.y < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
						&& m_position.y >  rectangles.at(i)->getPosition().y){

							m_position.x = rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x + m_radius;

					}
					if(m_position.y + m_radius > rectangles.at(i)->getPosition().y 
						&& m_position.y + m_radius < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
						&& m_position.x < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
						&& m_position.x >  rectangles.at(i)->getPosition().x){

							m_position.y = rectangles.at(i)->getPosition().y - m_radius;

					}
					if(m_position.y - m_radius > rectangles.at(i)->getPosition().y 
						&& m_position.y - m_radius < rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y
						&& m_position.x < rectangles.at(i)->getPosition().x + rectangles.at(i)->getSize().x
						&& m_position.x >  rectangles.at(i)->getPosition().x){

							m_position.y = rectangles.at(i)->getPosition().y + rectangles.at(i)->getSize().y + m_radius;

					}
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
		}

	}
	m_body.setPosition(m_position);
}

PlayerObject::~PlayerObject(void)
{
}

void PlayerObject::Draw()
{
	m_window->draw(m_body);
};