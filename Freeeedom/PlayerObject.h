#pragma once

#include "GameObject.h"

class InputManager;

class PlayerObject : public GameObject
{
public:
	PlayerObject(InputManager* inputmngr, sf::RenderWindow* window);

	bool Initialize();
	void Update(float deltatime);
	void WallCollision(std::vector<sf::RectangleShape*> rectangles);
	void Draw();

	~PlayerObject(void);

private:
	sf::CircleShape m_body;
	float m_radius;
	InputManager* m_input;
	sf::RenderWindow* m_window;
	float m_friction;
	float m_previousmouspos;
	float m_rotationspeed;
	float m_viewdistance;
	int m_numbercount[5];
};

