#pragma once

class Wall;
class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	virtual void Update(float deltatime) = 0;
	void WallCollision(std::vector<Wall*>& rectangles);
	void Draw(sf::RenderWindow* p_window);

	bool GetExistance();
	float GetRotation();
	sf::Vector2f GetCameraAnchor();
	sf::Vector2f GetPosition();

protected:

	bool m_existance;
	sf::CircleShape m_body;
	float m_radius;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_acceleration;

	float m_rotationspeed;
	float m_rotation;
	float m_rotationamount;

	sf::Vector2f m_cameraanchor;
	float m_viewdistance;

	float m_weight;
	float m_friction;

	sf::RenderWindow* m_window;

};

