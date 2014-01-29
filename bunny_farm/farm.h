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
	//Pointers to hold male and female bunnies:
	std::vector<bunny*> vFemaleAliveBunnies;
	std::vector<bunny*> vMaleAliveBunnies;

	//these two vectors contains the available names:
	std::vector<string> vstrMaleNames;
	std::vector<string> vstrFemaleNames;

	int nRNG_SEED;
	int nXSize;
	int nYSize;
	int nEmptyTiles; //keeps track of the # of empty tiles
	int nYear;

	//Initialization related:
	terrain myTerrain; //terrain object to generate the terrain
	void generateFarm();
	void generateSettings();
	std::vector<string> generateNames(const string filename);

	//Useful utilities:
	unsigned int getRandomNumber(const int , const int ); 
	int mapIndex (const int nXLoc, const int nYLoc);
	string namifyString (const string strString);
	string genBunnyName(string strGender);

	//Location related
	//valid location to generate a bunny
	bool validLocation(const int nXLoc, const int nYLoc); 
	//valid location to move a bunny 
	bool moveableLocation(const int  nXLoc,const int nYLoc);
	
	//Move a bunny to a location
	void moveBunny(bunny *pBunny);
	void updateMove(bunny *pBunny, const int nNewXLoc = -1, const int nNewYLoc = -1);

	//Age related:
	void updateAge();
		
	//Death:
	void killBunny(bunny *pBunny, const string strReason);

public:
	//~farm();
	farm();
	farm(const int nSeed); //default width/length, input RNG seed
	farm(const int nX,const int nY); //input width/length, default RNG seed
	farm(const int nSeed, const int nX, const int nY); //input width/length and RNG seed

	int getSizeX() { return nXSize; }
	int getSizeY() { return nYSize; }
	int getYear()  { return nYear; }
	tile getTile(const int x, const int y);
	//std::string getTerrain(int);
	//std::string genTerrain();
	void printFarm();
	bool createBunny(bunny *pNewMother, bunny *pNewFather, const int nXLoc = -1, const int nYLoc = -1);
	void simTurn();

};

#endif
