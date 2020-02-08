#include "Bullet.h"
#include<Crusty/ResourceManager.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
}


Bullet::~Bullet()
{
}


void Bullet::draw(Crusty::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Crusty::GLTexture texture = Crusty::ResourceManager::getTexture("player.png");

	Crusty::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posAndSize + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);

}

bool Bullet::update()
{
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0)
		return true;
	return false;
}