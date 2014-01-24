#ifndef __FARM_H
#define __FARM_H

#include <string>
#include <vector>
#include "tile.h"
#include "terrain.h"
#include "bunny.h"
#include <map>

using std::string;

class farm {
private:
	std::vector<tile>  myFarm;
	//This vector of bunnys contains the list of the bunnies
	//This list will continously be added to as bunnies are born
	//Dead bunnies will not be removed, but only have their attribute bDead set to true
	//Thus, this vector will be a list of all the bunnies ever created ordered by their birth date
	std::vector<bunny> vBunnyList;
	//this is a hash with bunny's name as the key and the pointer to
	//the bunny as the value
	std::map<string,bunny*> hBunnyName; 
	
	int nRNG_SEED;
	int nXSize;
	int nYSize;
	int nEmptyTiles; //keeps track of the # of empty tiles
	terrain myTerrain;

	unsigned int getRandomNumber(const int , const int ); 
	void generateFarm();
	int mapIndex (const int nXLoc, const int nYLoc);

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
	bool createBunny(bunny *pNewMother, bunny *pNewFather, const int nXLoc = -1, const int nYLoc = -1);
	bool validLocation(const int nXLoc, const int nYLoc);
};

#endif
