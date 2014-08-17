#pragma once
#include "Solid.h"
class GameObject;

class WallCorner : public Solid
{
public:
	WallCorner(sf::Vector2f p_position, sf::Vector2f p_size, int p_corner);
	~WallCorner(void);
	void Update(GameObject* p_player);
	void Draw(sf::RenderWindow& p_renderer);
	void DrawShadows(sf::RenderWindow& p_renderer);
	string GetType() {return "Corner";};

	sf::RectangleShape GetWall();

private:
	int m_corner;
};

