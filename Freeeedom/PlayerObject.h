#pragma once

#include "GameObject.h"

class InputManager;
class WeaponObject;

struct Weapon
{
	WeaponType weapontype;
	float weight;
	float sharpness;
	float length;
	float hitboxsize;
};

class PlayerObject : public GameObject
{
public:
	PlayerObject(InputManager* inputmngr, sf::RenderWindow* window);

	bool Initialize();
	void Update(float deltatime);
	void WallCollision(std::vector<sf::RectangleShape*> rectangles);
	void Draw();
	void Hit(std::vector<sf::CircleShape*> circles);
	void Attack();
	float GetStrength();
	float GetDeltaMouse();
	Weapon GetWeapon();
	sf::Vector2f GetSocket(int i);
	~PlayerObject(void);

private:

	Weapon m_weaponstats;
	WeaponObject* m_weapon;
	sf::CircleShape m_body;
	float m_radius;
	InputManager* m_input;
	sf::RenderWindow* m_window;
	float m_friction;
	float m_previousmouspos;
	float m_rotationspeed;
	float m_viewdistance;
	int m_numbercount[5];
	float m_strength;
	float m_weight;
	float m_deltamouse;
	bool m_released;
	bool m_loading;
	sf::Vector2f m_previousposition;
	sf::Vector2f m_actualvelocity;
	sf::Vector2f m_socketone;
	sf::Vector2f m_sockettwo;
};