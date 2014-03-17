#pragma once

class Engine;
class GameObject;

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
	bool m_cleared;
	std::vector<sf::RectangleShape*> m_rectangles;
};

