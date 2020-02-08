#include "Player.h"

#include "Gun.h"

Player::Player()
{
	_currentGunIndex = -1;// means no gun
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position, Crusty::InputManager* inputManager , Crusty::Camera2D* Camera,
	std::vector<Bullet>* bullets)
{
	_speed = speed;
	_position = position;
	_color.r = 100;
	_color.g = 100;
	_color.b = 255;
	_color.a = 255;	
	_inputmgr = inputManager;
	_Camera = Camera;
	_bullets = bullets;
}

void Player::addGun(Gun* gun)
{
	_guns.push_back(gun);
	//if no gun equipped, equip a gun
	if (_currentGunIndex == -1)
	{
		_currentGunIndex = 0;
	}
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
	if (_inputmgr->isKeyDown(SDLK_w))
	{
		_position.y += _speed;
	}
	if (_inputmgr->isKeyDown(SDLK_s))
	{
		_position.y -= _speed;
	}
	if (_inputmgr->isKeyDown(SDLK_a))
	{
		_position.x -= _speed;
	}
	if (_inputmgr->isKeyDown(SDLK_d))
	{
		_position.x += _speed;
	}

	if (_inputmgr->isKeyDown(SDLK_1) && _guns.size() >= 0)
	{
		_currentGunIndex = 0;
	}
	else if (_inputmgr->isKeyDown(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIndex = 1;
	}
	else if (_inputmgr->isKeyDown(SDLK_3) && _guns.size() >= 2)
	{
		_currentGunIndex = 2;
	}
	if (_currentGunIndex != -1)
	{
		
		glm::vec2 mousecoords = _inputmgr->getMouseCoord();
		
		// it is in screen space we will use the camera class to convert it into world space.
		mousecoords =_Camera->ScreenToWorld(mousecoords);
		glm::vec2 centerPosition = _position + glm::vec2(AGENTRADIUS);
		glm::vec2 dir = glm::normalize(mousecoords - centerPosition);

		_guns[_currentGunIndex]->update(_inputmgr->isKeyDown(SDL_BUTTON_LEFT),
			centerPosition,
			dir,
			*_bullets);
	}
	collideWithLevel(levelData);
}
