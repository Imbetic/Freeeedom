#pragma once
#include "Solid.h"
class WallEdge :
	public Solid
{
public:
	WallEdge(sf::Vector2f p_position, sf::Vector2f p_size, int p_edge);
	~WallEdge(void);
	void Update(GameObject* p_player);
	void Draw(sf::RenderWindow& p_renderer);
	void DrawShadows(sf::RenderWindow& p_renderer);
	string GetType() {return "Edge";};

	sf::RectangleShape GetWall();

private:
	int m_edge;
};

