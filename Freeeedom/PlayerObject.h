//#pragma once
//
//#include "Humanoid.h"
//
//class InputManager;
//class Wall;
//
//class PlayerObject : public Humanoid
//{
//public:
//	PlayerObject(InputManager* inputmngr, sf::RenderWindow* p_window);
//
//	void Update(float deltatime);
//	void Draw();
//	void Attack();
//	float GetStrength();
//	float GetDeltaMouse();
//
//	sf::Vector2f GetAnchor();
//
//	~PlayerObject(void);
//
//private:
//
//	InputManager* m_input;
//	float m_previousmouspos;
//	float m_rotationspeed;
//	float m_viewdistance;
//	float m_strength;
//	float m_deltamouse;
//	bool m_released;
//	bool m_loading;
//	sf::Vector2f m_cameraanchor;
//};