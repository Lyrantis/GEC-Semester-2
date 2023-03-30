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
	void SetTileAt(unsigned int row, unsigned int column, unsigned int new_value);

private:
	
	int** m_map;

};

#endif // !_LEVELMAP_H
