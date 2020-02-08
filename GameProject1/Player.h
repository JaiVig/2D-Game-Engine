#pragma once
#include<SDL.h>
#include"Human.h"
#include<Crusty/InputManager.h>
#include"Bullet.h"
#include<Crusty/Camera2D.h>

class Gun;
class Player :public Human
{
public:
	Player();
	~Player();
	void init(float speed,glm::vec2 position, Crusty::InputManager* inputManager, Crusty::Camera2D* Camera,
		std::vector<Bullet>* bullets);
	
	void addGun(Gun* gun);

	 void update(const std::vector<std::string>& levelData,
		 std::vector<Human*>& humans,
		 std::vector<Zombie*>& zombies);
private:
	Crusty::InputManager* _inputmgr;
	std::vector<Gun*> _guns;
	int _currentGunIndex;
	Crusty::Camera2D* _Camera;

	std::vector<Bullet>* _bullets;
};

