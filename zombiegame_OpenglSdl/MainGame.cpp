#include "MainGame.h"
#include<iostream>
#include<string>
#include<Crusty/Error.h>
#include<glm/glm.hpp>
#include"Crusty/ResourceManager.h"
MainGame::MainGame()
{
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
	_time = 0;
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initApi();
	
	gameLoop();
}

void MainGame::initApi()
{
	//initialize
	Crusty::init();
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
}

void MainGame::initShaders()
{
	
	_colorProgram.compileShaders("Shaders/vertexshader.vert.txt", "Shaders/fragshader.frag.txt");
	
	_colorProgram.addAttr("vertexPosition");
	_colorProgram.addAttr("vertexColor");
	_colorProgram.addAttr("vertexUV");

	_colorProgram.linkShaders();
	
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1;
		_camera.update();
		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
				i++;
		}
		drawGame();
		calculateFps();
		//std::cout << _fps << std::endl;
	}
}

void MainGame::processInput()
{
	const float CAMERASPEED = 10.0f;	
	const float CAMERAZOOM = 0.1f;
	
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;	
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
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoord(evnt.motion.x, evnt.motion.y);
			break;
		}
	}
	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERASPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERASPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERASPEED,0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERASPEED,0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + CAMERAZOOM);
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - CAMERAZOOM);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoord();
		mouseCoords = _camera.ScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << "  " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 10.0f, 1000);
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _colorProgram.getUniformLocation("playerTexture");
	glUniform1i(textureLocation, 0);

	//GLint timelocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timelocation, _time);

	GLint Plocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMat();
	glUniformMatrix4fv(Plocation, 1, GL_FALSE,
		&(cameraMatrix)[0][0]);

	_spriteBatch.begin();
	glm::vec4 position(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Crusty::GLTexture texture = Crusty::ResourceManager::getTexture("player.png");
	Crusty::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_spriteBatch.draw(position + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D,0);
	_colorProgram.unuse();

	_window.swapBuffers();
}

void MainGame::calculateFps()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks= SDL_GetTicks();

	_frameTime = currentTicks - previousTicks;
	previousTicks = currentTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	int count;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
		count = NUM_SAMPLES;
	float avgframetime = 0;
	for (int i = 0; i < count; i++)
	{
		avgframetime += frameTimes[i];
	}
	avgframetime /= count;

	if (avgframetime > 0)
	{
		_fps = 1000.0f / avgframetime;
	}
	else
	{
		_fps = 60.0f;
	}
	currentFrame++;
}

