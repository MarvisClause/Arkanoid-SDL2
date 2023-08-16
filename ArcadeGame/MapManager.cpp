#include "MapManager.h"
#include "GameSettings.h"
#include "MyFramework.h"
//-------------------------//
#include<iostream>

MapManager::MapManager(MyFramework* framework)
{
	this->framework = framework;

	SetMap();
}

void MapManager::SetMap()
{
	srand(time(NULL));
	int num = rand() % 3;

	map = Maps[num];
}

std::vector<vector2f> MapManager::GetBlocks()
{
	std::ifstream in(map);

	if (!in.is_open())
	{
		std::cout << "Error! - Can`t open map file!" << std::endl;
		throw std::invalid_argument("Error! - Can`t open map file!");
		framework->Close();
	}

	vector2f coord;
	std::vector<vector2f> block_coords;

	int map_w, map_h;
	framework->GetScreenSize(map_w, map_h);
	float pos_x_displ, pos_y_displ;

	pos_x_displ = static_cast<float>(map_w) / 1000.;
	pos_y_displ = static_cast<float>(map_h) / 800.;

	while (in >> coord.x && in >> coord.y)
	{
		coord.x *= pos_x_displ;
		coord.y *= pos_y_displ;
		block_coords.push_back(coord);
	}
	return block_coords;
}

