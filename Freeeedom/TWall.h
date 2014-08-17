#pragma once
#include "Solid.h"
class TWall :
	public Solid
{
public:
	TWall(sf::Vector2f p_position, sf::Vector2f p_size, int p_blankside);
	~TWall(void);
	void Update(GameObject* p_player);
	void Draw(sf::RenderWindow& p_renderer);
	void DrawShadows(sf::RenderWindow& p_renderer);
	string GetType() {return "T";};

	sf::RectangleShape GetWall();

private:
	int m_blankside;
};

