#pragma once
#include<glm/glm.hpp>
#include<Crusty/SpriteBatch.h>
class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();
	void draw(Crusty::SpriteBatch& spriteBatch);
	bool update(); //returns true when lifetime has ended

private:
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _lifeTime;
};

