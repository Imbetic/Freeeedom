#pragma once
#include "state.h"
class GameOverState :
	public State
{
public:
	GameOverState(Engine* engine);
	~GameOverState(void);
	/* Called upon entering state */
	bool EnterState();
	/* Called when changing state and old state exits */
	void ExitState();
	/* Parameter Deltatime
	Handles State Update */
	bool Update(float p_fDeltatime);
	/* Draws State*/
	void Draw();
	/* Returns True if Type == &p_type is same as State */
	bool IsType(const std::string &p_sType);
	/* Returns Current State */
	std::string GetCurrentState();
private:
	Engine* m_engine;
};

