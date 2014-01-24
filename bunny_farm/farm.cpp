/*Main cpp file*/
#include "farm.h"  //Uncomment this when separating header and cpp

#include <iostream>

#define NUM_NAME_GEN_TRIES 1000

using std::cout;
using std::endl;

farm::farm() {
	nRNG_SEED = 0;
	nXSize = 10;
	nYSize = 10;
	myTerrain.setSeed(nRNG_SEED);
	generateFarm();
}

farm::farm(const int nSeed) {
	nRNG_SEED = nSeed;
	nXSize = 10;
	nYSize = 10;
	myTerrain.setSeed(nRNG_SEED);
	generateFarm();
}

farm::farm(const int nX, const int nY) {
	nRNG_SEED = 0;
	nXSize = nX;
	nYSize = nY;
	myTerrain.setSeed(nRNG_SEED);
	generateFarm();
}

farm::farm(const int nSeed, const int nX, const int nY) {
	nRNG_SEED = nSeed;
	nXSize = nX;
	nYSize = nY;
	myTerrain.setSeed(nRNG_SEED);
	generateFarm();
}

void farm::generateFarm() {
	//Generate the terrains of the farm. This should be done during construction and should only be called by the constructor
	//Create the terrain:
	nEmptyTiles = nXSize*nYSize;
	for (int nX = 0; nX < nXSize; ++nX) {
		for (int nY = 0; nY < nYSize; ++nY) {
			myFarm.push_back(myTerrain.genTerrain());
			if (!myFarm.back().bPassable || myFarm.back().bFatal) {
				nEmptyTiles--;
			}
		}
	}
}

tile farm::getTile(const int x, const int y) {
	int nNewX = std::max(0,std::min(x,nXSize));
	int nNewY = std::max(0,std::min(y,nYSize));
	return myFarm[mapIndex(nNewX,nNewY)];
}

void farm::printFarm() {

	cout << endl;
	for (int nY = 0; nY < nYSize; ++nY) {
		cout << "      " ;
		for (int nX = 0; nX < nXSize; ++nX) {
			if (myFarm[mapIndex(nX,nY)].bOccupied) {
				//cout << (*myFarm[mapIndex(nX,nY)].pBunny).getSymbol();
				cout << myFarm[mapIndex(nX,nY)].pBunny->getSymbol();
			} else {
				cout << myFarm[mapIndex(nX,nY)].strSymbol ;
			}
		}
		cout << endl;
	}
	cout << endl;
}

unsigned int farm::getRandomNumber(const int nLow, const int nHigh) {
	return (rand() % (nHigh - nLow + 1)) + nLow;
}
int farm::mapIndex (const int nXLoc, const int nYLoc) {
	return nYLoc*nXSize+nXLoc;
}

bool farm::validLocation(const int nXLoc, const int nYLoc) {
	if ((nXLoc < 0) || (nYLoc < 0) || (nXLoc >= nXSize) || (nYLoc >= nYSize)) {
		//Check boundary conditions
		return false;
	} else {
		//Check valid creation location:
		if ((myFarm[mapIndex(nXLoc,nYLoc)].bFatal)    || \
			(myFarm[mapIndex(nXLoc,nYLoc)].bOccupied) || \
			!(myFarm[mapIndex(nXLoc,nYLoc)].bPassable)    ) {
				return false;
		}
	}
	return true;
}

bool farm::createBunny(bunny *pNewMother, bunny *pNewFather, const int nXLoc /*= -1*/, const int nYLoc /*= -1*/) {
	//The pNewMother and pNewFather pointers are pointers to the parents of the new bunny. If they are null, then it means 
	//They are the initial bunnies
	//creates a bunny object with age 0, at (nXLoc, nYLoc). If (nXLoc, nYLoc) is less than -1, then the placement is random
	//if any of the X or Y location is greater than the size of the farm, then the placement is random
	//Bunnys will not be created on any fatal or inpassable tiles nor will it be placed on an occupied tile
	if (nEmptyTiles <= 0) {
		//No empty tiles
		return false;
	}
	int nX = nXLoc;
	int nY = nYLoc;

	while (!validLocation(nX,nY)) {
		nX = getRandomNumber(0,nXSize);
		nY = getRandomNumber(0,nYSize);
	}

	//Generate the gender:
	bool bMale;
	if (getRandomNumber(0,1) == 0) {
		bMale = false;
	} else {
		bMale = true;
	}
	//TODO: Implement random name function:
	//string strBName = genBunnyName(bMale);
	string strBName = "Cole";
	//check the name hash for valid name:
	/*int count = 0;
	while (hBunnyName.count(strBName) == 1) {
		//generate new names
		string strBName = genBunnyName(bMale);
		if (count >= NUM_NAME_GEN_TRIES) {
			std::cerr << "ERROR: Cannot Generate Unique Names!!\n" ;
			return false;
		}
		//strBName 
	}*/

	//Create the new Bunny
	vBunnyList.push_back(bunny(strBName, bMale, pNewMother, pNewFather));
	//if the bunny's parents exists, update their OffSprings
	if (pNewMother!=NULL) {
		//cout << " HEERE!!" << endl;
		pNewMother->addOffSpring(&(vBunnyList.back()));
	}
	if (pNewFather!=NULL) {
		pNewFather->addOffSpring(&(vBunnyList.back()));
	}
	//Update the bunny name hash:
	hBunnyName[strBName] = &(vBunnyList.back());
	
	//Update the farm variables:
	nEmptyTiles--;
	myFarm[mapIndex(nX,nY)].bOccupied = true;
	myFarm[mapIndex(nX,nY)].pBunny = &(vBunnyList.back());
	cout << "A new bunny, " << strBName << ", was born!" << endl;
	
	return true;
}
