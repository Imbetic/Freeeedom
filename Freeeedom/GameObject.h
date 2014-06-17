#pragma once

class Wall;
class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	virtual bool Initialize() = 0;
	virtual void Update(float deltatime) = 0;
	virtual void WallCollision(std::vector<Wall*> rectangles) = 0;
	virtual void Hit(std::vector<sf::CircleShape*> circles) = 0;

	bool GetExistance();
	float GetRotation();
	sf::Vector2f GetPosition();
	sf::Vector2f GetAnchor();
	sf::Vector2f GetWeaponPosition();
	virtual void Draw() = 0;

protected:
	bool m_existance;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_acceleration;
	float m_rotation;
	sf::Vector2f m_weaponposition;
	sf::Vector2f m_cameraanchor;
};

