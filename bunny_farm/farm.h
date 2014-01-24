#ifndef __FARM_H
#define __FARM_H

#include <string>
#include <vector>
#include "tile.h"
#include "terrain.h"

using std::string;

class farm {
private:
	std::vector<tile> myFarm;
	int nRNG_SEED;
	int nXSize;
	int nYSize;
	terrain myTerrain;

	unsigned int getRandomNumber(const int , const int ); 
	void generateFarm();

public:
	farm();
	farm(const int nSeed); //default width/length, input RNG seed
	farm(const int nX,const int nY); //input width/length, default RNG seed
	farm(const int nSeed, const int nX, const int nY); //input width/length and RNG seed

	int getSizeX() { return nXSize; }
	int getSizeY() { return nYSize; }
	tile getTile(const int x, const int y) ;
	//std::string getTerrain(int);
	//std::string genTerrain();
	void printFarm();

};

#endif
