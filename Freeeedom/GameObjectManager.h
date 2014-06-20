#pragma once

class Engine;
class GameObject;
class Wall;
class Humanoid;

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

	bool m_cleared;
	std::vector<Wall*> m_walls;
};

