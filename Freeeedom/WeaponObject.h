#pragma once
#include "gameobject.h"

class PlayerObject;
class InputManager;

class WeaponObject :
	public GameObject
{
public:
	WeaponObject(PlayerObject* player, InputManager* input);
	~WeaponObject();
	
	bool Initialize();
	void Update(float deltatime);
	void WallCollision(std::vector<sf::RectangleShape*> rectangles);
	void Hit(std::vector<sf::CircleShape*> circles);
	void Draw();
	void Load(bool loading);
private:
	WeaponType m_weapontype;
	PlayerObject* m_player;
	sf::CircleShape m_body;
	InputManager* m_input;
	sf::Vector2f m_start;
	float m_load;
	float m_maxload;
	float m_loadspeed;
	float m_weight;
	float m_sharpness;
	float m_length;
};