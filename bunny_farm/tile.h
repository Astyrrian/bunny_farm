#ifndef __TILE_H
#define __TILE_H

#include <string>

struct tile {

	//Set during initialization
	std::string strName;
	std::string strSymbol;
	bool bPassable;
	bool bFatal;

	//Only used during generation
	int nChance;

	//Only changed during simulation
	bool bOccupied;

};


#endif
