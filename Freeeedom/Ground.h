#pragma once
class Ground
{
public:
	Ground(sf::Vector2i p_sizetimes32, sf::Vector2f p_position);
	void Draw(sf::RenderWindow& p_renderer);
	sf::RectangleShape GetSquare();
	~Ground(void);
private:
	sf::RectangleShape m_ground;
	float m_friction;
};