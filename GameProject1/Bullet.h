#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<Crusty/SpriteBatch.h>
#include<string>
#include"Level.h"
class Human;
class Zombie;
const int BulletRadius = 5.0f;
class Agent;
class Bullet
{
public:
	Bullet(int damage, glm::vec2 position, glm::vec2 dir, float speed);
	bool update(const std::vector<std::string>& levelData);
	void draw(Crusty::SpriteBatch& spriteBatch);
	bool collideWithAgent(Agent* Agent);
	float getDamage()const { return _damage; }
private:
	bool collideWithWorld(const std::vector<std::string>& levelData);
	int _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};

