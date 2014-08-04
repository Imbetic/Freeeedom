#include "stdafx.h"
#include "Humanoid.h"
#include "Brain.h"
#include "MeleeWeapon.h"

Humanoid::Humanoid(Brain* p_brain)
{
	m_meleeweapon = new MeleeWeapon(50, 10, 10);
	m_brain = p_brain;
	//m_brain->Update();
	m_acceleration = 1500;
	m_friction = 10;
	m_radius = 32;
	m_position = sf::Vector2f(100, 100);
	m_body.setPosition(m_position);
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Black);
	m_rotationspeed = 12;
	m_strength = 1000;

	m_rotation = 0;
	m_body.setRotation(m_rotation);
	m_viewdistance = 250;
	m_swingspeed = 0;
	m_swingfriction = 20;

	m_releaseswing = false;
	m_swingingleft = false;
	m_swingingright = false;
	m_loadleft = false;
	m_loadright = false;

	m_hand.setPosition(sf::Vector2f(100, 110));
	m_hand.setRadius(m_radius/3);
	m_hand.setOrigin(m_radius/3, m_radius/3);
	m_hand.setFillColor(sf::Color::Black);

	m_relativehandposition = sf::Vector2f(30*cos(1), 30*sin(1));


}

void Humanoid::Update(float deltatime)
{
	m_brain->Update();

	Rotation(deltatime);
	Movement(deltatime);

	PreUpdateHand();

	if(m_releaseswing) ReleaseAttack();

	if(m_swingingleft || m_swingingright) Swinging(deltatime);
	else if(m_loadleft || m_loadright) LoadAttack(deltatime);
	else IdleHand(deltatime);

	PostUpdateHand(deltatime);

	m_meleeweapon->Update((m_armangle*2)+m_rotation+90, m_hand.getPosition());

	m_cameraanchor = sf::Vector2f(m_position.x+(m_viewdistance*-cos(m_rotation*3.141592654f/180)), m_position.y+(m_viewdistance*-sin(m_rotation*3.141592654f/180)));
}

void Humanoid::PreUpdateHand()
{
	{
		//Movement from body rotation

		m_relativehandposition.x = 35*cos(3.141592654f*(m_hand.getRotation() + m_rotationamount)/180);
		m_relativehandposition.y = 35*sin(3.141592654f*(m_hand.getRotation() + m_rotationamount)/180);

		m_hand.setRotation(atan2(m_relativehandposition.y, m_relativehandposition.x) *180/3.141592654f);
	}

	m_previousarmangle = m_armangle;
	m_armangle = m_hand.getRotation() - m_body.getRotation();
	if(m_armangle < 0) m_armangle += 360;
	else if (m_armangle >= 360) m_armangle -= 360;

	if(!m_loadleft && !m_loadright) CheckStartLoading();
}

void Humanoid::PostUpdateHand(float deltatime)
{
	if(m_armangle < 90)
	{
		m_swingspeed = 0;
		m_relativehandposition.x = 35*cos(3.141592654f*(m_body.getRotation()+90.1)/180);
		m_relativehandposition.y = 35*sin(3.141592654f*(m_body.getRotation()+90.1)/180);
		m_armangle = 90.1;
	}
	if(m_armangle > 270)
	{
		m_swingspeed = 0;
		m_relativehandposition.x = 35*cos(3.141592654f*(m_body.getRotation()-90.1)/180);
		m_relativehandposition.y = 35*sin(3.141592654f*(m_body.getRotation()-90.1)/180);
		m_armangle = 269.9;
	}

	m_swingvelocity = sf::Vector2f(m_swingspeed * -sin(m_hand.getRotation()*3.141592654f/180), m_swingspeed * cos(m_hand.getRotation()*3.141592654f/180));

	if(m_swingspeed != 0)
	{
		m_swingvelocity.x += m_swingvelocity.x * deltatime * m_swingfriction;
		m_swingvelocity.y += m_swingvelocity.y * deltatime * m_swingfriction;

		m_relativehandposition.x += m_swingvelocity.x * deltatime;
		m_relativehandposition.y += m_swingvelocity.y * deltatime;
	}
	//The hand cannot leave the invisible arm!
	float distance = sqrt((m_relativehandposition.x * m_relativehandposition.x) + (m_relativehandposition.y * m_relativehandposition.y));
	if(distance == 0) distance = 0.001;
	if(distance > 30)
	{
		float offset = distance - 30;
		m_relativehandposition.x -= offset*(m_relativehandposition.x)/distance;
		m_relativehandposition.y -= offset*(m_relativehandposition.y)/distance;
	}
	//The hand's final position is set
	m_hand.setPosition(sf::Vector2f(m_body.getPosition().x + m_relativehandposition.x, m_body.getPosition().y + m_relativehandposition.y));

}

void Humanoid::CheckStartLoading()
{
	if(m_brain->GetLoadAttack() && m_rotationamount <= 0)
	{
		m_existance = false;
		m_loadleft = true;
		if(!m_swingingleft && !m_swingingright) m_swingspeed = 0;
	}
	else if(m_brain->GetLoadAttack() && m_rotationamount > 0)
	{
		m_loadright = true;
		if(!m_swingingleft && !m_swingingright) m_swingspeed = 0;
	}
};

void Humanoid::IdleHand(float deltatime)
{

	{
		//Idle movement towards idle state
		if(m_armangle >= 180)
		{
			if(m_previousarmangle < 180)
			{ 
				m_swingspeed = 0;
				m_relativehandposition.x = 35*cos(3.141592654f*(m_body.getRotation()-180)/180);
				m_relativehandposition.y = 35*sin(3.141592654f*(m_body.getRotation()-180)/180);
			}
			else
			{
				m_swingspeed -= m_strength * deltatime /m_meleeweapon->GetWeight();
			}
		}
		else if (m_armangle < 180)
		{
			if(m_previousarmangle >= 180)
			{ 
				m_swingspeed = 0;
				m_relativehandposition.x = 35*cos(3.141592654f*(m_body.getRotation()-180)/180);
				m_relativehandposition.y = 35*sin(3.141592654f*(m_body.getRotation()-180)/180);
			}
			else
			{
				m_swingspeed += m_strength * deltatime/m_meleeweapon->GetWeight();
			}
		}
	}

}

void Humanoid::Rotation(float deltatime)
{
	m_rotationamount = m_brain->GetRotationAmount()*m_rotationspeed/200;
	m_rotation+= m_rotationamount;
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
	if(m_loadleft)
	{
		m_swingspeed -= 2* m_strength * deltatime/m_meleeweapon->GetWeight();
	}
	else if (m_loadright)
	{
		m_swingspeed += 2* m_strength * deltatime/m_meleeweapon->GetWeight();
	}
	if(!m_brain->GetLoadAttack())
	{
		m_loadleft = false;
		m_loadright = false;
		m_releaseswing = true;
	}
}

void Humanoid::ReleaseAttack()
{
	m_swingspeed = 0;
	m_releaseswing = false;
	if(m_armangle < 180)
	{
		m_swingingright = true;
	}
	else if(m_armangle > 180)
	{
		m_swingingleft = true;
	}
}

void Humanoid::Swinging(float deltatime)
{
	int t_swingdirection;
	if(m_swingingleft)
	{
		/*if(m_armangle > 180)*/ m_swingspeed -= m_strength*2*deltatime/m_meleeweapon->GetWeight();
		/*else */if(m_armangle <= 90) m_swingingleft = false;
	}
	else if(m_swingingright)
	{
		/*if(m_armangle < 180)*/ m_swingspeed += m_strength*2*deltatime/m_meleeweapon->GetWeight();
		/*else*/ if(m_armangle >= 270) m_swingingright = false;
	};
}

void Humanoid::Draw(sf::RenderWindow* p_window)
{
	p_window->draw(m_body);
	p_window->draw(m_hand);
	p_window->draw(m_meleeweapon->GetBody());
	p_window->draw(m_meleeweapon->GetHandle());
}

Humanoid::~Humanoid(void)
{
	delete m_brain;
	m_brain = nullptr;
	delete m_meleeweapon;
	m_meleeweapon = nullptr;
}
