#pragma once
#include "Agent.h"
#include<string>

class Zombie :public Agent
{
public:
	Zombie();

	void init(float speed, glm::vec2 pos);
	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	private:
		Human* getNearestHuman(std::vector<Human*>& humans);
};

