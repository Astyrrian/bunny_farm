/*Terrain Class*/

#include "terrain.h"
#include <cstdlib>
//#include <iostream>


terrain::terrain() {

	genTerrainAttr();
	//Default seed of 0
	nRNG_SEED = 0;
	std::srand(terrain::nRNG_SEED);

}

terrain::terrain(int nRandSeed) {
	//Populate the default terrain types:
	genTerrainAttr();
	nRNG_SEED = nRandSeed;
	std::srand(terrain::nRNG_SEED);

}

void terrain::genTerrainAttr() {
	//generates the default type attributes. Perhaps in the future, this can be read from a config file

	tile grass;
	grass.strName = "grass";
	grass.strSymbol = "-";
	grass.bFatal = false;
	grass.bPassable = true;
	grass.nChance = 80;
	grass.bOccupied = false;
	
	tile mountain;
	mountain.strName = "mountain";
	mountain.strSymbol = "^";
	mountain.bFatal = false;
	mountain.bPassable = false;
	mountain.nChance = 15;
	mountain.bOccupied = false;

	tile lava;
	lava.strName = "lava";
	lava.strSymbol = "O";
	lava.bFatal = true;
	lava.bPassable = true;
	lava.nChance = 5;
	lava.bOccupied = false;

	aTerrainType.push_back(grass);
	aTerrainType.push_back(mountain);
	aTerrainType.push_back(lava);

	nTerrainTypeSize = 3;

	//update the chance vector
	int prev = 0;
	for (std::vector<tile>::iterator it = aTerrainType.begin() ; it != aTerrainType.end(); ++it) {
		anTerrainChance.push_back((*it).nChance + prev);
		prev = anTerrainChance.back();
		//std::cout << anTerrainChance.back() << std::endl;
	}
	
	nTotalChance = anTerrainChance.back();

}
/*
std::string terrain::getTerrain(int nTerrainNum) {
	if (nTerrainNum >= terrain::nTerrainTypeSize) {
		return "INVALID";
	} else {
		return terrain::astrTerrainType[nTerrainNum];
	} 
}*/

tile terrain::genTerrain() {

	int nRand = terrain::getRandomNumber(0, nTotalChance-1);
	int nIdx = 0;
	tile ter;
	//std::cout << nRand << std::endl;
	do {
		//TODO: make this a binary search to be faster
		//std::cout << "  " << nIdx << "  :   " << terrain::anTerrainChance[nIdx] << std::endl;
		nIdx++;
	} while (terrain::anTerrainChance[nIdx-1] < nRand ) ;
	//The correct index is nIdx - 1
	ter = aTerrainType[nIdx-1];

	return ter;

}

unsigned int terrain::getRandomNumber(int nLow, int nHigh) {
	return (rand() % (nHigh - nLow + 1)) + nLow;
}
