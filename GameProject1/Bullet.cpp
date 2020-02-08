#include "Bullet.h"
#include<Crusty/ResourceManager.h>
#include"Agent.h"
#include"Human.h"
#include"Zombie.h"
Bullet::Bullet(int damage, glm::vec2 position, glm::vec2 dir, float speed)
{
	_damage = damage;
	_position = position;
	_direction = dir;
	_speed = speed;
}

bool Bullet::update(const std::vector<std::string>& levelData)
{
	_position += _direction * _speed;
	return collideWithWorld(levelData);
}

void Bullet::draw(Crusty::SpriteBatch& spriteBatch)
{
	glm::vec4 destRec(_position.x + BulletRadius
						, _position.y + BulletRadius,
						BulletRadius * 2,
						BulletRadius * 2);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Crusty::ColorRGBA8 color;
	color.r = 128;
	color.g = 128;
	color.b = 75;
	color.a = 255;
	spriteBatch.draw(destRec,uvRect, Crusty::ResourceManager::getTexture("Textures/Circle.png").id, 0.0f,color);
}

bool Bullet::collideWithAgent(Agent* Agent)
{
	// Minimum distance before there is a collision
	const float MIN_DISTANCE = AGENTRADIUS + BulletRadius;

	// Center position of bullet
	glm::vec2 centerPosA = _position;
	// Center position of the parameter agent
	glm::vec2 centerPosB = Agent->getPosition() + glm::vec2(AGENTRADIUS);

	// Distance vector between the two agents
	glm::vec2 distVec = centerPosA - centerPosB;

	// Length of the distance vector
	float distance = glm::length(distVec);

	// Depth of the collision
	float collisionDepth = MIN_DISTANCE - distance;

	// If collision depth > 0 then we did collide
	if (collisionDepth > 0) {

		return true;
	}
	return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);
	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].length() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size())
	{
		return true;//delete bullet
	}
	return (levelData[gridPosition.y][gridPosition.x] != '.');
}
