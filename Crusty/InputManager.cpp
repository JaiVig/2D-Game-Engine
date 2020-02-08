#include "InputManager.h"


namespace Crusty {
	InputManager::InputManager()
	{
		_mouseCoord = glm::vec2(0.0f,0.0f);
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		//loop through keymap states and copy it over to previous keymap
		for(auto& iter : _keyMap)
		{
			_previousKeyMap[iter.first] = iter.second;
		}
	}
	void InputManager::pressKey(unsigned int keyID)
	{
		_keyMap[keyID] = true;
	}
	void InputManager::releaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}
	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
			return it->second;

		return false;
	}
	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		//check if its pressed this frame and wasnt pressed last frame
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
		{
			return true;
		}
		return false;
	}
	void InputManager::setMouseCoord(float x, float y)
	{
		_mouseCoord.x = x;
		_mouseCoord.y = y;
	}
	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end())
			return it->second;

		return false;
	}
}