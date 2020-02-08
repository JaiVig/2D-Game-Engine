#pragma once
#include<unordered_map>
#include<glm/glm.hpp>
namespace Crusty {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		void update();
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		//returns true if the key is held down
		bool isKeyDown(unsigned int keyID);
		//returns true if the key is tapped just this frame
		bool isKeyPressed(unsigned int keyID);
		void setMouseCoord(float x, float y);
		glm::vec2 getMouseCoord() const { return _mouseCoord; }

	private:
		bool wasKeyDown(unsigned int keyID);
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoord;
	};
}	
