#pragma once
#include<glm/glm.hpp>
#include<Crusty/GLTexture.h>
#include<Crusty/SpriteBatch.h>
#include<string>

const float AGENT_WIDTH = 60;
const float AGENTRADIUS = (float)AGENT_WIDTH / 2.0f;
class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();
	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;
	bool collideWithLevel(const std::vector<std::string>& levelData);
	 
	bool collideWithAgent(Agent* agent);
	void draw(Crusty::SpriteBatch& _spriteBatch);
	//getters
	glm::vec2 getPosition()const { return _position; }
	//returns true if we die
	bool applyDamage(float damage);
protected:
	void checkTilePosition(const std::vector<std::string>& levelData,
							std::vector<glm::vec2>& collideTilePositions,
							float x, 
							float y);
	void collideWithTile(glm::vec2 tilePos);
	glm::vec2 _position;
	float _speed;
	Crusty::ColorRGBA8 _color;
	float _health;
};

