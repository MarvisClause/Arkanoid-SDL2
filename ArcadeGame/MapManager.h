#pragma once

#include "BaseObject.h"
#include "vector2f.h"
#include<vector>
#include<fstream>

class MyFramework;

class MapManager : public BaseObject
{
public:
	MapManager(MyFramework* framework);

	void SetMap();

	std::vector<vector2f> GetBlocks();

private:

	std::string map;

	const char* Maps[3] = {
		"maps/map1.txt",
		"maps/map2.txt",
		"maps/map3.txt"
	};

	MyFramework* framework;
};