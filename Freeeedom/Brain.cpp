#include "stdafx.h"
#include "Brain.h"


Brain::Brain(void)
{
}

bool Brain::GetMovement(int number)
{
	return m_movement[number];
}

bool Brain::GetRun()
{
	return m_run;
}

float Brain::GetRotationAmount()
{
	return m_rotationamount;
}

Brain::~Brain(void)
{
}
