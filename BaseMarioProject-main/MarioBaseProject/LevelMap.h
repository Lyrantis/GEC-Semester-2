#pragma once

#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "Constants.h"

class LevelMap
{

public:

	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int w, unsigned int h);

private:
	
	int** m_map;
	LevelMap* m_level_map;

	void SetLevelMap();

};

#endif // !_LEVELMAP_H
