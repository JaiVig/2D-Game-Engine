#pragma once
#include<string>
#include<vector>
#include<glm/glm.hpp>
#include"Bullet.h"
class Gun
{
public:
	Gun(std::string name, int firerate, int bulletsPerShot, float Spread, float bulletSpeed, float bulletDamage);
	
	void update(bool isMouseDown,const glm::vec2& position, const glm::vec2& dir, std::vector<Bullet>& Bullets);
private:
	void fire(const glm::vec2& dir, const glm::vec2& position, std::vector<Bullet>& Bullets);
	std::string _name;
	int _firerate; //in terms of frames 
	int _bulletsPerShot; //how many bullets fired at a time
	float _spread; //accuracy
	float _bulletSpeed;
	float _bulletDamage;
	int _frameCounter;
};

