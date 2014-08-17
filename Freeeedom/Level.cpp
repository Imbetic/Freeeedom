#include "stdafx.h"
#include "Level.h"
#include "Solid.h"
#include "WallCorner.h"
#include "WallEdge.h"
#include "TWall.h"
#include "Wall.h"

Level::Level(void)
{
}

void Level::CreateLevel(std::vector<Solid*>& p_walls)
{
	std::vector<std::string> lines;
	std::string line;
	std::ifstream t_level ("../Data/Level.txt");

	if (t_level.is_open())
	{
		while ( getline (t_level,line) )
		{
			lines.push_back(line);
		}
		t_level.close();
	}
	for(int i = 0; i<lines.size(); i++)
	{

		for(int u = 0; u<lines.at(i).size(); u++)
		{
			if(lines.at(i).at(u) == *"W")
			{
				p_walls.push_back(new TWall(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 0));
			}
			if(lines.at(i).at(u) == *"D")
			{
				p_walls.push_back(new TWall(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 1));
			}
			if(lines.at(i).at(u) == *"S")
			{
				p_walls.push_back(new TWall(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 2));
			}
			if(lines.at(i).at(u) == *"A")
			{
				p_walls.push_back(new TWall(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 3));
			}
			if(lines.at(i).at(u) == *"7")
			{
				p_walls.push_back(new WallCorner(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 0));
			}
			if(lines.at(i).at(u) == *"9")
			{
				p_walls.push_back(new WallCorner(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 1));
			}
			if(lines.at(i).at(u) == *"3")
			{
				p_walls.push_back(new WallCorner(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 2));
			}
			if(lines.at(i).at(u) == *"1")
			{
				p_walls.push_back(new WallCorner(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 3));
			}
			if(lines.at(i).at(u) == *"8")
			{
				p_walls.push_back(new WallEdge(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 0));
			}
			if(lines.at(i).at(u) == *"6")
			{
				p_walls.push_back(new WallEdge(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 1));
			}
			if(lines.at(i).at(u) == *"2")
			{
				p_walls.push_back(new WallEdge(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 2));
			}
			if(lines.at(i).at(u) == *"4")
			{
				p_walls.push_back(new WallEdge(sf::Vector2f(32*u, 32*i), sf::Vector2f(32, 32), 3));
			}
			if(lines.at(i).at(u) == *"5")
			{
				if(lines.at(i).at(u-1) != *"5" && lines.at(i-1).at(u) != *"5")
				{
					if(lines.at(i).at(u-1) == *"0" && lines.at(i).at(u+1) == *"0")
					{
						bool temparray[4] = {true, false, true, false};
						Wall* tempwall = new Wall(sf::Vector2f(u*32, i*32), sf::Vector2f(32, 32), temparray);
						int tempmove = 1;
						while(lines.at(i+tempmove).at(u) == *"5")
						{
							tempwall->SetSize(sf::Vector2f(0, 32));
							tempmove++;
						}
						p_walls.push_back(tempwall);
					}
					else if(lines.at(i-1).at(u) == *"0" && lines.at(i+1).at(u) == *"0")
					{
						bool temparray[4] = {false, true, false, true};
						Wall* tempwall = new Wall(sf::Vector2f(u*32, i*32), sf::Vector2f(32, 32), temparray);
						int tempmove = 1;
						while(lines.at(i).at(u+tempmove) == *"5")
						{
							tempwall->SetSize(sf::Vector2f(32, 0));
							tempmove++;
						}
						p_walls.push_back(tempwall);
					}
				}
				else if(lines.at(i).at(u-1) == *"5")
				{

				}
				else if(lines.at(i-1).at(u) == *"5")
				{

				}
			}
		}
	}
	lines.clear();
}

Level::~Level(void)
{
}
