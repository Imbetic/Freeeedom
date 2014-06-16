#pragma once

class PlayerObject;

class Wall
{
public:
	Wall(sf::Vector2f p_position, sf::Vector2f p_size);
	~Wall(void);
	void Update(PlayerObject* p_player);
	void Draw(sf::RenderWindow* p_renderer);
	void DrawShadows(sf::RenderWindow* p_renderer);
private:

	sf::RectangleShape m_wall;
	sf::RectangleShape m_shadowaim;

	sf::ConvexShape m_shadow[4];

};

