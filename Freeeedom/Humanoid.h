#pragma once

#include "GameObject.h"

class Brain;

class Humanoid : public GameObject
{
public:
	Humanoid(Brain* p_brain);
	void Update(float deltatime);
	void Movement(float deltatime);
	void Rotation(float deltatime);
	void LoadAttack(float deltatime);
	void ReleaseAttack(float deltatime);
	~Humanoid(void);

private:
	Brain* m_brain;

};

