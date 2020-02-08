#include "Agent.h"
#include<Crusty/ResourceManager.h>
#include"Level.h"
#include<stdlib.h>
#include<iostream>
#include<algorithm>
Agent::Agent()
{
}


 Agent::~Agent()
{
}

 void Agent::update(const std::vector<std::string>& levelData,
	 std::vector<Human*>& humans,
	 std::vector<Zombie*>& zombies)
 {

 }

 bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
 {
	 std::vector<glm::vec2> collideTilePositions;

	 //check the 4 corners

	//first corner
	 checkTilePosition(levelData, collideTilePositions, _position.x, _position.y);
	 //2nd corner
	 checkTilePosition(levelData, collideTilePositions, _position.x + AGENT_WIDTH, _position.y);

	 checkTilePosition(levelData, collideTilePositions, _position.x, _position.y+AGENT_WIDTH);

	 checkTilePosition(levelData, collideTilePositions, _position.x+ AGENT_WIDTH, _position.y +AGENT_WIDTH);
	 if (collideTilePositions.size() == 0)
		 return false;
	 for (int i = 0; i < collideTilePositions.size(); i++)
	 {
		
		 collideWithTile(collideTilePositions[i]);
	 }

	 return true;
 }

 bool Agent::applyDamage(float damage)
 {
	 _health -= damage;
	 if (_health <= 0)
	 {
		 return true;
	 }
	 return false;
 }

 void Agent::checkTilePosition(const std::vector<std::string>& levelData,
	 std::vector<glm::vec2>& collideTilePositions,
	 float x,
	 float y)
 {
	 glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		 floor(y / (float)TILE_WIDTH));
	 //if we are outside the world just return
	 if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		 cornerPos.y < 0 || cornerPos.y >= levelData.size())
	 {
		 return;
	 }
	 if (levelData[cornerPos.y][cornerPos.x] != '.')
	 {
		 collideTilePositions.push_back((cornerPos * (float)TILE_WIDTH) + glm::vec2((float)TILE_WIDTH / 2.0f));
	 }

 }
 
 bool Agent::collideWithAgent(Agent* agent) {

	 // Minimum distance before there is a collision
	 const float MIN_DISTANCE = AGENTRADIUS * 2.0f;

	 // Center position of this agent
	 glm::vec2 centerPosA = _position + glm::vec2(AGENTRADIUS);
	 // Center position of the parameter agent
	 glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENTRADIUS);

	 // Distance vector between the two agents
	 glm::vec2 distVec = centerPosA - centerPosB;

	 // Length of the distance vector
	 float distance = glm::length(distVec);

	 // Depth of the collision
	 float collisionDepth = MIN_DISTANCE - distance;

	 // If collision depth > 0 then we did collide
	 if (collisionDepth > 0) {

		 // Get the direction times the collision depth so we can push them away from each other
		 
		 glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		 // Push them in opposite directions
		 _position += collisionDepthVec / 2.0f;
		 agent->_position -= collisionDepthVec / 2.0f;

		 return true;
	 }
	 return false;
 }

 void Agent::draw(Crusty::SpriteBatch& _spriteBatch)
 {
	 static int textureId = Crusty::ResourceManager::getTexture("Textures/circle.png").id;
	 glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	 
	 

	 _spriteBatch.draw(destRect, glm::vec4(0.0f,0.0f,1.0f,1.0f),textureId,0,_color);
 }

 

 //AABB collision
 void Agent::collideWithTile(glm::vec2 tilePos)
 {
	
	 const float TILERADIUS = (float)TILE_WIDTH / 2.0f;
	 const float MIN_DIST = AGENTRADIUS + TILERADIUS;
	 glm::vec2 centerPos = _position + glm::vec2(AGENTRADIUS);
	 glm::vec2 distVect = centerPos - tilePos;
	 
	 float xDepth = MIN_DIST - abs(distVect.x);
	 float yDepth = MIN_DIST - abs(distVect.y);

	 if (xDepth > 0 || yDepth > 0) // we are colliding
	 {
		 if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		 {
			 if (distVect.x < 0)
			 {
				 _position.x -= xDepth;
			 }
			 else
			 {
				 _position.x += xDepth;
			 }
		 }
		 else {
			 if (distVect.y < 0)
			 {

				 _position.y -= yDepth;
			 }
			 else
			 {
				 _position.y += yDepth;
			 }
		 }
	 }
 }
