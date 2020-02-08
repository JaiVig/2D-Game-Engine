#include "Camera2D.h"


namespace Crusty {
	Camera2D::Camera2D() : _position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenwidth(500),
		_screenheight(500),
		_orthoMatrix(1.0f)
	{}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenwidth = screenWidth;
		_screenheight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenwidth, 0.0f, (float)_screenheight);
	}

	glm::vec2 Camera2D::ScreenToWorld(glm::vec2 screenCoords)
	{
		//invert y dir
		screenCoords.y = _screenheight - screenCoords.y;
		//make it so that 0,0 is the center
		screenCoords -= glm::vec2(_screenwidth / 2, _screenheight / 2);
		//scale the coordinates
		screenCoords /= _scale;
		//translate with camera position
		screenCoords += _position;
		return screenCoords;
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			glm::vec3 translate(-_position.x + _screenwidth / 2, -_position.y + _screenheight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f),scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}
	}


}