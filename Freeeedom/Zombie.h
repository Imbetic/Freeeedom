#pragma once
#include "GameObject.h"

class Humanoid;
class Solid;

class Zombie :
	public GameObject
{
public:
	Zombie(sf::Vector2f p_position);
	void Update(float deltatime){};
	void Update(float deltatime, sf::Vector2f p_playerposition);

	void CheckIfHit(Humanoid& p_player);

	~Zombie(void);
private:

	bool m_previousplayervision;
	bool m_playervision;
	bool m_chase;
	sf::Vector2f m_target;
};

