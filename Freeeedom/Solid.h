#pragma once

class GameObject;

class Solid
{
public:
	Solid();
	virtual ~Solid(void){};
	virtual void Update(GameObject* p_player) = 0;
	virtual void Draw(sf::RenderWindow& p_renderer) = 0;
	virtual void DrawShadows(sf::RenderWindow& p_renderer) = 0;
	virtual string GetType() = 0;
	void SetSize(sf::Vector2f p_increasement);

	void GetShadows(sf::ConvexShape p_shadows[4], sf::RectangleShape p_shadowaim);
	virtual sf::RectangleShape GetWall() = 0;

protected:

	sf::RectangleShape m_wall;
	sf::RectangleShape m_shadowaim;

	sf::Vector2f m_playerposition;

	sf::ConvexShape m_shadow[4];

	bool m_shadowsides[4];
};

