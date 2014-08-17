#pragma once

class Solid;

class Level
{
public:
	Level();
	void CreateLevel(std::vector<Solid*>& p_walls);
	~Level();
};

