#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(void)
{
	m_existance = true;
	m_position = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = 0;
	m_rotation = 0;

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

sf::Vector2f GameObject::GetAnchor()
{
	return m_cameraanchor;
}