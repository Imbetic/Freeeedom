#pragma once
class State;
class StateManager
{
public:

	StateManager();
	~StateManager();
	/* Returns Current State as String */
	string CurrentState();
	string NextState();
	/* Attaches new State to StateManager */
	void Attach(State *p_pState);
	/* Calls CurrentStates Update */
	void Update(float p_fDeltatime);
	/* Calls CurrentStates Draw */
	void Draw();
	/* Changes CurrentState into string parameter*/
	void SetState(const string &p_sType);
	void SetNextState(const string &p_sType);
	/* Returns True while running */
	bool IsRunning();

	State* GetCurrentState();

private:
	/* Vector of States*/
	vector<State*> m_aStates;
	/* Current State Pointer*/
	State *m_pCurrentState;
	std::string m_NextState;
};

