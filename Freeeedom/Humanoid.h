#pragma once

#include "GameObject.h"

class Brain;
class MeleeWeapon;

class Humanoid : public GameObject
{
public:
	Humanoid(Brain* p_brain);
	void Update(float deltatime);
	void PreUpdateHand();
	void PostUpdateHand(float deltatime);
	void IdleHand(float deltatime);
	void Movement(float deltatime);
	void Rotation(float deltatime);
	void LoadAttack(float deltatime);
	void ReleaseAttack();
	void Swinging(float deltatime);
	void Draw(sf::RenderWindow& p_window);
	void CheckStartLoading();
	void ZombieCollision(sf::CircleShape p_zombiebody);

	bool SwingCheck();
	sf::CircleShape GetWeaponHead();

	~Humanoid(void);

private:

	bool m_loadright;
	bool m_loadleft;
	bool m_loading;
	bool m_releaseswing;
	bool m_swingingleft;
	bool m_swingingright;

	Brain* m_brain;
	sf::CircleShape m_hand;

	MeleeWeapon* m_meleeweapon;

	float m_armangle;
	float m_previousarmangle;

	float m_strength;
	float m_swingfriction;
	float m_swingspeed;
	sf::Vector2f m_swingvelocity;
	sf::Vector2f m_relativehandposition;

};

