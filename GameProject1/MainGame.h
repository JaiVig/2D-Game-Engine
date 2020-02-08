#pragma once

#include <Crusty\Windows.h>
#include <Crusty\GLSLshader.h>
#include <Crusty\Camera2D.h>
#include <Crusty\InputManager.h>
#include<Crusty/SpriteBatch.h>
#include"Gun.h"
#include"Bullet.h"
#include"Level.h"
#include"Player.h"
class Zombie;
enum class GameState {
	PLAY,
	EXIT
};
class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();
	/// Initializes the shaders
	void initShaders();
	void initLevel();
	void checkVictory();
	/// Main game loop for the program
	void gameLoop();
	void updateBullets();
	void updateAgents();
	/// Handles input processing
	void processInput();
	/// Renders the game
	void drawGame();

private:
	/// Member Variables
	Crusty::Windows _window; ///< The game window
	Crusty::GLSLshader _textureProgram; ///< The shader program
	Crusty::InputManager _inputManager; ///< Handles input
	Crusty::Camera2D _camera; ///< Main Camera
	Crusty::SpriteBatch _agentSpriteBatch;
	std::vector<Level*> _levels; // vectors of all level
	std::vector<Human*> _humans;//vector of all humans
	std::vector<Zombie*> _zombies;//vector of all zpmbies
	std::vector<Bullet> _bullets;
	Player* _player;
	int _screenWidth, _screenHeight;
	GameState gamestate;
	int _currentLevel;
	float a = 0.0f;
	int frames = 0;
	int _numHumansKilled;
	int _numZombiesKilled;
};

