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
	m_strength = 10;

	m_rotation = 0;
	m_body.setRotation(m_rotation);
	m_viewdistance = 250;
	m_swingspeed = 0;

	m_hand.setPosition(sf::Vector2f(100, 110));
	m_hand.setRadius(m_radius/3);
	m_hand.setOrigin(m_radius/3, m_radius/3);
	m_hand.setFillColor(sf::Color::Black);

	m_relativehandposition = sf::Vector2f(35*cos(1), 35*sin(1));


}

void Humanoid::Update(float deltatime)
{
	m_brain->Update();

	Rotation(deltatime);
	Movement(deltatime);

	LoadAttack(deltatime);
	IdleHand(deltatime);
	ReleaseAttack(deltatime);



	m_cameraanchor = sf::Vector2f(m_position.x+(m_viewdistance*-cos(m_rotation*3.141592654f/180)), m_position.y+(m_viewdistance*-sin(m_rotation*3.141592654f/180)));
}

void Humanoid::IdleHand(float deltatime)
{
	{
		//Movement from body rotation

		float bodyrotationmovement = m_brain->GetRotationAmount()*deltatime*m_rotationspeed;

		m_relativehandposition.x = 35*cos(3.141592654f*(m_hand.getRotation() + bodyrotationmovement)/180);
		m_relativehandposition.y = 35*sin(3.141592654f*(m_hand.getRotation() + bodyrotationmovement)/180);

		m_hand.setRotation(atan2(m_relativehandposition.y, m_relativehandposition.x) *180/3.141592654f);
	}

	{
		//Idle movement towards idle state
		m_swingspeed += m_strength * deltatime;

		m_swingvelocity = sf::Vector2f(m_swingspeed * -sin(m_hand.getRotation()*3.141592654f/180), m_swingspeed * cos(m_hand.getRotation()*3.141592654f/180));

		m_relativehandposition.x += m_swingvelocity.x * deltatime;
		m_relativehandposition.y += m_swingvelocity.y * deltatime;
	}

	{
		//The hand cannot leave the invisible arm!
		float distance = sqrt((m_relativehandposition.x * m_relativehandposition.x) + (m_relativehandposition.y * m_relativehandposition.y));

		if(distance > 35)
		{
			float offset = distance - 35;
			m_relativehandposition.x -= offset*(m_relativehandposition.x)/distance;
			m_relativehandposition.y -= offset*(m_relativehandposition.y)/distance;
		}
	}

	//The hand's final position is set
	m_hand.setPosition(sf::Vector2f(m_body.getPosition().x + m_relativehandposition.x, m_body.getPosition().y + m_relativehandposition.y));
}

void Humanoid::Rotation(float deltatime)
{
	m_rotation+= m_brain->GetRotationAmount()*deltatime*m_rotationspeed;
	if(m_rotation >=360) m_rotation -= 360;
	if(m_rotation < 0) m_rotation += 360;

	m_body.setRotation(m_rotation);

	m_hand.setRotation(atan2(m_relativehandposition.y, m_relativehandposition.x) *180/3.141592654f);
}

void Humanoid::Movement(float deltatime)
{
	if(m_brain->GetMovement(0) || m_brain->GetMovement(1) || m_brain->GetMovement(2) || m_brain->GetMovement(3)) //Check what movement is desired, 8 possible.
	{
		if(m_brain->GetMovement(0) && m_brain->GetMovement(1) && m_brain->GetMovement(2) && m_brain->GetMovement(3)){}
		else
		{
			const float pi = 3.141592654f;

			if(m_brain->GetRun()&&m_brain->GetMovement(0))
			{
				m_acceleration = 3000;
			}
			else m_acceleration = 1500;

			float accY=0;
			float accX=0;

			if(m_brain->GetMovement(0) && m_brain->GetMovement(1) && m_brain->GetMovement(2))
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
			else
			{
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
		}
	};

	m_position += m_velocity * deltatime;
	m_velocity.x-=m_velocity.x*m_friction*deltatime;
	m_velocity.y-=m_velocity.y*m_friction*deltatime;
	m_body.setPosition(m_position);
	m_hand.setPosition(sf::Vector2f(m_body.getPosition().x + m_relativehandposition.x, m_body.getPosition().y + m_relativehandposition.y)); //Updates hand position so that angular calculations will work more precisely
}

void Humanoid::LoadAttack(float deltatime)
{

}

void Humanoid::ReleaseAttack(float deltatime)
{

}

void Humanoid::Draw(sf::RenderWindow* p_window)
{
	p_window->draw(m_body);
	p_window->draw(m_hand);
}

Humanoid::~Humanoid(void)
{
}
