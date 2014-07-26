#pragma once

class MeleeWeapon
{
public:
	MeleeWeapon(float p_handlelength, float p_bodysize, float p_weight);
	void Update(float angle, sf::Vector2f p_position);
	~MeleeWeapon(void);

	sf::CircleShape GetBody();
	sf::RectangleShape GetHandle();

	float GetWeight();

private:
	float m_weight;
	sf::CircleShape m_body;
	sf::RectangleShape m_handle;
};

