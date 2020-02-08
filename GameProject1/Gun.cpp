#include "Gun.h"
#include<random>
#include<ctime>
#include<glm/gtx/rotate_vector.hpp>
Gun::Gun(std::string name, int firerate, int bulletsPerShot, float Spread, float bulletSpeed, float bulletDamage)
{
	_name = name;
	_firerate = firerate;
	_bulletsPerShot = bulletsPerShot;
	_spread = Spread;
	_bulletSpeed = bulletSpeed;
	_bulletDamage = bulletDamage;
	_frameCounter = 0;
}

void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& dir, std::vector<Bullet>& Bullets)
{
	_frameCounter++;
	if (_frameCounter >= _firerate && isMouseDown)
	{
		fire(dir, position,Bullets);
		_frameCounter = 0;
	}
}

void Gun::fire(const glm::vec2& dir, const glm::vec2& position, std::vector<Bullet>& Bullets)
{
	 static std::mt19937 randomEngine(time(nullptr));
	 std::uniform_real_distribution<float>randRotate(-_spread, _spread);
	for (int i = 0; i < _bulletsPerShot; i++)
	{

		Bullets.emplace_back(_bulletDamage,position,glm::rotate(dir,randRotate(randomEngine)), _bulletSpeed);
	}
}
