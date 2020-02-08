#pragma once
#include<string>
#include<vector>
#include<Crusty/SpriteBatch.h>
#include<Crusty/ResourceManager.h>
const int TILE_WIDTH = 64;
class Level
{
public:
	Level(const std::string& fileName);
	~Level();
	void draw();
	// getters
	int getWidth()const { return _levelData[0].size(); }
	int getHeight()const { return _levelData.size(); }
	glm::vec2 getStartPlayerPos()const { return _startPlayerPosition; }
	int getNumHumans()const { return _numHumans; }
	
	const std::vector<glm::vec2>& getStartZombiePos() const { return _startZombiePositions; }
	const std::vector<std::string>& getLevelData()const { return _levelData; }
private:
	int _numHumans;
	std::vector<std::string> _levelData;
	Crusty::SpriteBatch _spriteBatch;
	glm::vec2 _startPlayerPosition;
	std::vector<glm::vec2> _startZombiePositions;
};

