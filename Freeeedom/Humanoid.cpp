#include "stdafx.h"
#include "Humanoid.h"
#include "Brain.h"

Humanoid::Humanoid(Brain* p_brain)
{
	m_brain = p_brain;
	m_brain->Update();
	m_acceleration = 1500;
	m_friction = 10;
	m_radius = 25;
	m_position = sf::Vector2f(100, 100);
	m_body.setPosition(m_position);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Black);
	m_rotationspeed = 12;
	m_rotation = 0;
	m_body.setRotation(m_rotation);
	m_viewdistance = 250;
}

void Humanoid::Update(float deltatime)
{
	m_brain->Update();

	LoadAttack(deltatime);
	Rotation(deltatime);
	Movement(deltatime);
	ReleaseAttack(deltatime);
	m_cameraanchor = sf::Vector2f(m_position.x+(m_viewdistance*-cos(m_rotation*3.141592654f/180)), m_position.y+(m_viewdistance*-sin(m_rotation*3.141592654f/180)));
}

void Humanoid::Rotation(float deltatime)
{
	std::cout << deltatime << std::endl;
	std::cout << m_rotationspeed << std::endl;
	std::cout << m_brain->GetRotationAmount() << std::endl;
	m_rotation+= m_brain->GetRotationAmount()*deltatime*m_rotationspeed;
	m_body.setRotation(m_rotation);
}

void Humanoid::Movement(float deltatime)
{
	if(m_brain->GetMovement(0) || m_brain->GetMovement(1) || m_brain->GetMovement(2) || m_brain->GetMovement(3)){

		const float pi = 3.141592654f;

		if(m_brain->GetRun()&&m_brain->GetMovement(0))
		{
			m_acceleration = 3000;
		}
		else m_acceleration = 1500;

		float accY=0;
		float accX=0;
		if(m_brain->GetMovement(0) && m_brain->GetMovement(1) && m_brain->GetMovement(2) && m_brain->GetMovement(3)){}
		else if(m_brain->GetMovement(0) && m_brain->GetMovement(1) && m_brain->GetMovement(2))
		{
			accX=-cos((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
			accY=-sin((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
		}
		else if(m_brain->GetMovement(1) && m_brain->GetMovement(2) && m_brain->GetMovement(3))
		{
			accX=cos(m_rotation*pi/180) * m_acceleration  * deltatime;
			accY=sin(m_rotation*pi/180) * m_acceleration  * deltatime;
		}
		else if(m_brain->GetMovement(0) && m_brain->GetMovement(1) && m_brain->GetMovement(3))
		{
			accX=-cos(m_rotation*pi/180) * m_acceleration  * deltatime;
			accY=-sin(m_rotation*pi/180) * m_acceleration  * deltatime;
		}
		else if(m_brain->GetMovement(0) && m_brain->GetMovement(2) && m_brain->GetMovement(3))
		{
			accX=-cos((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
			accY=-sin((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
		}
		else{
			if(m_brain->GetMovement(0) && m_brain->GetMovement(2)){}
			else if(m_brain->GetMovement(0))
			{
				accX=-cos(m_rotation*pi/180) * m_acceleration  * deltatime;
				accY=-sin(m_rotation*pi/180) * m_acceleration  * deltatime;
			}
			else if(m_brain->GetMovement(2))
			{
				accX=cos(m_rotation*pi/180) * m_acceleration  * deltatime;
				accY=sin(m_rotation*pi/180) * m_acceleration  * deltatime;
			};

			if(m_brain->GetMovement(1) && m_brain->GetMovement(3)){}
			else if(m_brain->GetMovement(1))
			{
				accX=-cos((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation-90)*pi/180) * m_acceleration  * deltatime;
			}
			else if(m_brain->GetMovement(3)){
				accX=-cos((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation+90)*pi/180) * m_acceleration  * deltatime;
			};

			if(m_brain->GetMovement(0) && m_brain->GetMovement(3))
			{
				accX=-cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
			}

			else if(m_brain->GetMovement(0) && m_brain->GetMovement(1))
			{
				accX=-cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
				accY=-sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
			}

			else if(m_brain->GetMovement(1) && m_brain->GetMovement(2))
			{
				accX=cos((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
				accY=sin((m_rotation+45)*pi/180) * m_acceleration  * deltatime;
			}

			else if(m_brain->GetMovement(2) && m_brain->GetMovement(3))
			{
				accX=cos((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
				accY=sin((m_rotation-45)*pi/180) * m_acceleration  * deltatime;
			}
		}
		m_velocity += sf::Vector2f(accX, accY);
	};

	m_position += m_velocity * deltatime;
	m_velocity.x-=m_velocity.x*m_friction*deltatime;
	m_velocity.y-=m_velocity.y*m_friction*deltatime;
	m_body.setPosition(m_position);
}

void Humanoid::LoadAttack(float deltatime)
{

}

void Humanoid::ReleaseAttack(float deltatime)
{

}

Humanoid::~Humanoid(void)
{
}
