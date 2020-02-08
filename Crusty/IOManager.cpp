#include "IOManager.h"

#include<fstream>

namespace Crusty {
	bool IOManager::ReadFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filepath, std::ios::binary);
		if (file.fail())
		{
			perror(filepath.c_str());
			return false;
		}
		file.seekg(0, std::ios::end);
		int filesize = file.tellg();
		file.seekg(0, std::ios::beg);

		//remove extra header if present
		filesize -= file.tellg();
		buffer.resize(filesize);
		file.read((char*)&buffer[0], filesize);
		file.close();
		return true;
	}
}