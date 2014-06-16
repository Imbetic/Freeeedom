#include "stdafx.h"
#include "WeaponObject.h"
#include "PlayerObject.h"
#include "InputManager.h"


WeaponObject::WeaponObject(PlayerObject* player, InputManager* input)
{
	m_player = player;
	m_weight = m_player->GetWeapon().weight;
	m_length = m_player->GetWeapon().length;
	m_body.setRadius(m_player->GetWeapon().hitboxsize);
	m_sharpness = m_player->GetWeapon().sharpness;
	m_weapontype = m_player->GetWeapon().weapontype;
	m_input = input;
}

bool WeaponObject::Initialize()
{
	if(m_player->GetDeltaMouse()>0)
	{
		m_start = m_player->GetSocket(2);
	}
	else m_start = m_player->GetSocket(1);
	return true;
};

void Load(bool loading)
{

};

void WeaponObject::Update(float deltatime)
{
	m_acceleration = m_player->GetStrength();

	switch(m_weapontype)
	{
	case TWOHANDED:
		{
			
		};
	case ONEHANDED:
		{
		
		};
	case DUALWIELD:
		{
		
		};
	case WITHSHIELD:
		{
		
		};
	case RANGED:
		{
		
		};
	case TRIWIELD:
		{
		
		};
	}
};

void WeaponObject::WallCollision(std::vector<sf::RectangleShape*> rectangles)
{

};

void WeaponObject::Hit(std::vector<sf::CircleShape*> circles)
{

};

void WeaponObject::Draw()
{

};

WeaponObject::~WeaponObject(void)
{

};