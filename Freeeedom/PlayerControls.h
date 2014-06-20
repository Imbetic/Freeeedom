#pragma once

#include "Brain.h"

class InputManager;

class PlayerControls : public Brain
{
public:
	PlayerControls(InputManager* p_input, sf::RenderWindow* p_window);
	void Update();
	~PlayerControls(void);
private:
	sf::RenderWindow* m_window;
	InputManager* m_input;
	float m_previousmouspos;
};

