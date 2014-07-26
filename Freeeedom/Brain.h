#pragma once
class Brain
{
public:
	Brain(void);

	virtual void Update() = 0;
	bool GetMovement(int number);
	bool GetRun();
	bool GetLoadAttack();
	float GetRotationAmount();

	~Brain(void);



protected:
	bool m_movement[4];
	bool m_run;
	bool m_loadattack;
	float m_rotationamount;
};

