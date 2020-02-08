#pragma once
#include<SDL.h>
#include<GL/glew.h>
#include<Crusty/Crusty.h>
#include<Crusty/Sprite.h>
#include<Crusty/GLSLshader.h>
#include<Crusty/GLTexture.h>
#include<Crusty/Windows.h>
#include<Crusty/Camera2D.h>
#include<Crusty/SpriteBatch.h>
#include<Crusty/InputManager.h>
#include"Bullet.h"
#include<vector>
enum class GameState { PLAY, EXIT };
class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
	
private:
	void initApi();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFps();


	Crusty::Windows _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Crusty::GLSLshader _colorProgram;
	Crusty::Camera2D _camera;
	Crusty::SpriteBatch _spriteBatch;
	Crusty::InputManager _inputManager;
	float _time;
	float _fps;
	float _frameTime;

	std::vector<Bullet> _bullets;
};

