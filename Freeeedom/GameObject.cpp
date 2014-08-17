#include "stdafx.h"
#include "GameObject.h"
#include "Solid.h"
#include "Ground.h"


GameObject::GameObject(void)
{
	m_existance = true;
	m_position = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = 0;
	m_rotation = 0;
}

void GameObject::WallCollision(std::vector<Solid*>& rectangles)
{
	for(int i = 0; i<rectangles.size(); i++)
	{
		float t_maxdist;
		float deltaX = (rectangles.at(i)->GetWall().getPosition().x + (rectangles.at(i)->GetWall().getSize().x/2)) - m_position.x;
		float deltaY = (rectangles.at(i)->GetWall().getPosition().y + (rectangles.at(i)->GetWall().getSize().y/2)) - m_position.y;
		float dist = sqrtf((deltaX*deltaX)+(deltaY*deltaY));
		if(rectangles.at(i)->GetWall().getSize().x > rectangles.at(i)->GetWall().getSize().y)
		{
			t_maxdist = rectangles.at(i)->GetWall().getSize().x;
		}
		else
		{
			t_maxdist = rectangles.at(i)->GetWall().getSize().y;
		}
		if(t_maxdist < 100) t_maxdist = 100;
		if(dist < t_maxdist)
		{
			bool t_collision = false;

			if(m_position.x + m_radius > rectangles.at(i)->GetWall().getPosition().x 
				&& m_position.x + m_radius < rectangles.at(i)->GetWall().getPosition().x + rectangles.at(i)->GetWall().getSize().x
				&& m_position.y < rectangles.at(i)->GetWall().getPosition().y + rectangles.at(i)->GetWall().getSize().y
				&& m_position.y >  rectangles.at(i)->GetWall().getPosition().y){

					m_position.x = rectangles.at(i)->GetWall().getPosition().x - m_radius;
					m_body.setPosition(m_position);
					t_collision = true;

			}
			if(m_position.x - m_radius > rectangles.at(i)->GetWall().getPosition().x 
				&& m_position.x - m_radius < rectangles.at(i)->GetWall().getPosition().x + rectangles.at(i)->GetWall().getSize().x
				&& m_position.y < rectangles.at(i)->GetWall().getPosition().y + rectangles.at(i)->GetWall().getSize().y
				&& m_position.y >  rectangles.at(i)->GetWall().getPosition().y){

					m_position.x = rectangles.at(i)->GetWall().getPosition().x + rectangles.at(i)->GetWall().getSize().x + m_radius;
					m_body.setPosition(m_position);
					t_collision = true;

			}
			if(m_position.y + m_radius > rectangles.at(i)->GetWall().getPosition().y 
				&& m_position.y + m_radius < rectangles.at(i)->GetWall().getPosition().y + rectangles.at(i)->GetWall().getSize().y
				&& m_position.x < rectangles.at(i)->GetWall().getPosition().x + rectangles.at(i)->GetWall().getSize().x
				&& m_position.x >  rectangles.at(i)->GetWall().getPosition().x){

					m_position.y = rectangles.at(i)->GetWall().getPosition().y - m_radius;
					m_body.setPosition(m_position);
					t_collision = true;

			}
			if(m_position.y - m_radius > rectangles.at(i)->GetWall().getPosition().y 
				&& m_position.y - m_radius < rectangles.at(i)->GetWall().getPosition().y + rectangles.at(i)->GetWall().getSize().y
				&& m_position.x < rectangles.at(i)->GetWall().getPosition().x + rectangles.at(i)->GetWall().getSize().x
				&& m_position.x >  rectangles.at(i)->GetWall().getPosition().x){

					m_position.y = rectangles.at(i)->GetWall().getPosition().y + rectangles.at(i)->GetWall().getSize().y + m_radius;
					m_body.setPosition(m_position);
					t_collision = true;

			}

			if(!t_collision || rectangles.at(i)->GetType() != "Wall" || rectangles.at(i)->GetType() != "T")
			{
				for(int j = 0; j < 4; j++)
				{
					float dX = m_position.x - (rectangles.at(i)->GetWall().getPoint(j).x + rectangles.at(i)->GetWall().getPosition().x);
					float dY = m_position.y - (rectangles.at(i)->GetWall().getPoint(j).y + rectangles.at(i)->GetWall().getPosition().y);
					float dist = sqrt((dX*dX) + (dY*dY));
					if(dist == 0) dist = 0.1;


					if(dist<m_radius)
					{
						float overlapdist = m_radius - dist;
						float x = overlapdist * dX /dist;
						float y = overlapdist * dY /dist;
						m_position += sf::Vector2f(x, y);
						m_body.setPosition(m_position);
					};

				}
			}
		}

	}
}

void GameObject::GroundCollision(std::vector<Ground*>& p_grounds)
{
	for( int i = 0; i < p_grounds.size(); i++)
	{
		if(p_grounds.at(i)->GetSquare().getGlobalBounds().contains(m_position))
		{
			m_onground = true;
			break;
		}
		else
		{
			m_onground = false;
		}
	};

	if(!m_onground) m_existance = false;

}

void GameObject::Draw(sf::RenderWindow& p_window)
{
	p_window.draw(m_body);
}

sf::Vector2f GameObject::GetCameraAnchor()
{
	return m_cameraanchor;
}

GameObject::~GameObject(void)
{

}

bool GameObject::GetExistance()
{
	return m_existance;
}

sf::Vector2f GameObject::GetPosition()
{
	return m_position;
};

float GameObject::GetRotation()
{
	return m_rotation;
}

sf::CircleShape GameObject::GetBody()
{
	return m_body;
}