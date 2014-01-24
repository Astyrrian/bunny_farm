#ifndef __TERRAIN_H
#define __TERRAIN_H

#include <string>
#include <vector>
#include "tile.h"

class terrain {
private:
	/*struct types {
		std::string strName;
		std::string strSymbol;
		int nChance;
		bool bPassable;
		bool bFatal;
	};*/

	std::vector<tile> aTerrainType;
	std::vector<int> anTerrainChance; //Scores the likelihood of generating a certain terrain
	
	int nTotalChance; //Total  likelihood score of all terrains
	int nTerrainTypeSize;
	int nRNG_SEED;
	
	unsigned int getRandomNumber(const int , const int ); 
	void genTerrainAttr();

public:
	terrain();
	terrain(const int);
	int getSize() { return nTerrainTypeSize; }
	void setSeed(const int nSeed);
	//std::string getTerrain(int);
	tile genTerrain();


};

//#include "terrain.cpp"

#endif