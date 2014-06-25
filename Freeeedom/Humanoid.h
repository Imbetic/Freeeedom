#pragma once

#include "GameObject.h"

class Brain;

class Humanoid : public GameObject
{
public:
	Humanoid(Brain* p_brain);
	void Update(float deltatime);
	void IdleHand(float deltatime);
	void Movement(float deltatime);
	void Rotation(float deltatime);
	void LoadAttack(float deltatime);
	void ReleaseAttack(float deltatime);
	void Draw(sf::RenderWindow* p_window);
	~Humanoid(void);

private:

	bool m_right;
	bool m_left;
	bool m_loading;
	bool m_swinging;

	Brain* m_brain;
	sf::CircleShape m_hand;

	float m_strength;
	float m_swingspeed;
	sf::Vector2f m_swingvelocity;
	sf::Vector2f m_relativehandposition;

};

