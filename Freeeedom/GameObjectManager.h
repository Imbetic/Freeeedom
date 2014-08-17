#pragma once

class Level;
class Engine;
class GameObject;
class Solid;
class Humanoid;
class Ground;
class Zombie;

class GameObjectManager
{
public:
	GameObjectManager(Engine* engine);
	~GameObjectManager(void);

	bool Initialize();
	void Update(float deltatime);
	void Clear();
	void Draw();

private:
	Engine* m_engine;
	std::vector<GameObject*> m_gameobjects;
	Humanoid* m_player;

	Level* m_level;
	bool m_cleared;

	sf::RectangleShape m_goal;

	Zombie* m_zombies;
	std::vector<Solid*> m_walls;
	std::vector<Ground*> m_grounds;
	sf::RectangleShape m_leftviewlimit;
	sf::RectangleShape m_rightviewlimit;
	sf::RectangleShape m_backviewlimit;
};

