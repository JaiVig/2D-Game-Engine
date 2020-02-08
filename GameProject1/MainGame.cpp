#include "MainGame.h"
#include <SDL.h>
#include<iostream>
#include<Crusty/Crusty.h>
#include<Crusty/Error.h>
#include"Zombie.h"
#include<ctime>
#include<random>
const float HUMANSPEED = 1.0f;
const float ZOMBIESPEED = 3.0f;
const float PLAYERSPEED = 8.0f;
const float PI = 3.142857;
MainGame::MainGame() :_screenWidth(1920), _screenHeight(1080), gamestate(GameState::PLAY), _player(nullptr),_numHumansKilled(0),_numZombiesKilled(0)
{
	// Empty
}

MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}
}

void MainGame::run() {
	initSystems();
	initLevel();
	gameLoop();
}

void MainGame::initSystems() {
	Crusty::init();
	_window.create("Zombie Game", _screenWidth, _screenHeight, 0);
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	initShaders();
	_camera.init(_screenWidth, _screenHeight);
	_agentSpriteBatch.init();
}

void MainGame::initShaders() {
	// Compile our color shader
	_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.addAttr("vertexPosition");
	_textureProgram.addAttr("vertexColor");
	_textureProgram.addAttr("vertexUV");
	_textureProgram.linkShaders();
}
void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;
	_player = new Player();
	_player->init(PLAYERSPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager,&_camera,&_bullets);
	_humans.push_back(_player);

	 std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	 std::uniform_int_distribution<int>randX(2, _levels[_currentLevel]->getWidth() -2);
	 std::uniform_int_distribution<int>randY(2, _levels[_currentLevel]->getHeight() - 2);
	
	//add all random humans
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMANSPEED,pos);
	}
	//add zombies

	const std::vector<glm::vec2>& zombiePos = _levels[_currentLevel]->getStartZombiePos();
	for (int i = 0; i < zombiePos.size(); i++)
	{
		_zombies.push_back(new Zombie);
	
		_zombies.back()->init(ZOMBIESPEED, zombiePos[i]);
	}

	//setup Player Gun
	const float BULLETSPEED = 20.0f;
	_player->addGun(new Gun("Magnum", 20, 1, 0.01, BULLETSPEED,70.0f));
	_player->addGun(new Gun("Shotgun",30, 12, 0.4f, BULLETSPEED, 20.0f));
	_player->addGun(new Gun("MachineGun", 2, 1,0.07, BULLETSPEED, 18.0f));
}
void MainGame::gameLoop() {
	while (gamestate == GameState::PLAY)
	{
		checkVictory();
		_inputManager.update();
		processInput();
		updateAgents();
		updateBullets();
		_camera.setPosition(_player->getPosition());
		_camera.update();
		drawGame();
	}

}
void MainGame::checkVictory()
{
	//init the new level if we win
	if (_zombies.empty())
	{
		std::printf("***You Win!***\n You killed %d humans and %d zombies. There are %d/%d humans remaining", _numHumansKilled,_numZombiesKilled, _humans.size()-1, _levels[_currentLevel]->getNumHumans());
		Crusty::fatalError("");
	}
}
void MainGame::updateAgents()
{
	//update all humans
	for (int i = 0;i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans,_zombies);
	}

	//update zombies
	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}

	//Update human collision
	for (int i = 0; i < _humans.size(); i++)
	{
		//collide with other humans
		for (int j = i + 1; j < _humans.size(); j++)
		{
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}
	//update zombie collision
	for (int i = 0; i < _zombies.size(); i++)
	{ //collide with other zombies
		for (int j = i + 1; j < _zombies.size(); j++)
		{
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
		//collide with humans
		for (int k =  1; k < _humans.size(); k++)
		{
			if (_zombies[i]->collideWithAgent(_humans[k]))
			{
				//add new zombie at same place
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIESPEED, _humans[k]->getPosition());
				//delete the old human
				delete _humans[k];
				_humans[k] = _humans.back();
				_humans.pop_back();
				
			}
		}
		//collide with player
		if(_zombies[i]->collideWithAgent(_player))
		{
			//Crusty::fatalError("game over");
		}
	}
}
void MainGame::updateBullets() {
	//collide with level
	for (int i = 0; i < _bullets.size(); )
	{
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData()))
		{
			//bullet collided with wall
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else {
			i++;
		}
	}

	bool wasBulletRemoved;
	//collide with humans and zombies
	for (int i = 0; i < _bullets.size(); i++)
	{
		//loop through zombies
		wasBulletRemoved = false;
		for (int j = 0; j < _zombies.size();)
		{
			if (_bullets[i].collideWithAgent(_zombies[j]))
			{
				if (_zombies[j]->applyDamage(_bullets[i].getDamage()))
				{
					//if zombie dies, kill him
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
					_numZombiesKilled++;
				}
				else
				{
					j++;
				}
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletRemoved = true;
				i--;//make sure we dont skip a bullet
				break; //since bullet died no need to loop through more zombies
			}
			else {
				j++;
				
			}
		}
		//loop through humans
		if (wasBulletRemoved == false)
		{
			//starts from 1 to ignore collition with player
			for (int k = 1; k < _humans.size();)
			{
				if (_bullets[i].collideWithAgent(_humans[k]))
				{
					//damage human. kill it if its health is zero
					if (_humans[k]->applyDamage(_bullets[i].getDamage()))
					{
						//if zombie dies, kill him
						delete _humans[k];
						_humans[k] = _humans.back();
						_humans.pop_back();
						_numHumansKilled++;
					}
					else
					{
						k++;
					}
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					wasBulletRemoved = true;
					i--;//make sure we dont skip a bullet
					break; //since bullet died no need to loop through more zombies
				}
				else {
					k++;

				}
			}
		}
		// next bullet
		i++;
	}
}
void MainGame::processInput() {
	SDL_Event evnt;
	const float CAMERASPEED = 10.0f;
	const float CAMERAZOOM = 0.02f;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoord(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}

	}
	if (_inputManager.isKeyDown(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERASPEED));
	}
	if (_inputManager.isKeyDown(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERASPEED));
	}
	if (_inputManager.isKeyDown(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERASPEED, 0.0f));
	}
	if (_inputManager.isKeyDown(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERASPEED, 0.0f));
	}
	if (_inputManager.isKeyDown(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + CAMERAZOOM);
	}
	if (_inputManager.isKeyDown(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - CAMERAZOOM);
	}
}

void MainGame::drawGame() {
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	//Draw code goes here
	glActiveTexture(GL_TEXTURE0);
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glm::mat4 projectionMatrix = _camera.getCameraMat();

	GLint pUniform = _textureProgram.getUniformLocation("transformationMatrix");

	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_levels[_currentLevel]->draw();
	//draw humans
	_agentSpriteBatch.begin();
	

	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}
	
	//draw zombies
	
	
	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_agentSpriteBatch);
	}
	//draw bullets
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_agentSpriteBatch);
	}
	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	

	_textureProgram.unuse();
	//Swap our buffer and draw everything to the screen!
	_window.swapBuffers();
}