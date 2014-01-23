#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "conio.h"
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

#define SSTR(x) dynamic_cast <std::ostringstream&> (std::ostringstream()<<std::dec<<x).str()

#define FARM_SIZE_X 10
#define FARM_SIZE_Y 10
#define RNG_SEED  4321

struct farm {
	string strType;
	bool bOccupied;
};

namespace terrains {
	/*enum terrainType {
		dirt = 0,
		grass,
		rock,
		water,
		hole,
		lava,
		NUM_OF_ITEMS,
	};*/

	static const string astrTerrainType[] = { \
		"d", \
		"g", \
		"r", \
		"w", \
		"h", \
		"l" \
	};
	
	static const int nTerrainTypeSize = sizeof(astrTerrainType)/sizeof(string);

	string getTerrain(int nTerrainNum) {
		if (nTerrainNum >= nTerrainTypeSize) {
			return "INVALID";
		} else {
			return astrTerrainType[nTerrainNum];
		} 
	}

};

unsigned int GetRandomNumber(int nLow, int nHigh); 

void printFarm (farm *pFarm, const int nXSize, const int nYSize);

int main() {
	//Initialize the random number generator:
	std::srand(RNG_SEED);
	//Generate the farm:
	farm myFarm[FARM_SIZE_X][FARM_SIZE_Y];
	
	for (int nX = 0; nX < FARM_SIZE_X; ++nX) {
		for (int nY = 0; nY < FARM_SIZE_Y; ++nY) {
			int nRand = GetRandomNumber(0, terrains::nTerrainTypeSize-1);
			myFarm[nX][nY].strType = terrains::getTerrain(nRand);
			myFarm[nX][nY].bOccupied = false;
		}
	}
	printFarm(&myFarm[0][0], FARM_SIZE_X, FARM_SIZE_Y);
	_getch();
	return 0;
}

void printFarm (farm *pFarm, const int nXSize, const int nYSize) {
	for (int nX = 0; nX < nXSize; ++nX) {
		for (int nY = 0; nY < nYSize; ++nY) {
			cout << (*pFarm).strType ;
			pFarm++;
		}
		cout << endl;
	}
}

unsigned int GetRandomNumber(int nLow, int nHigh) {
    return (rand() % (nHigh - nLow + 1)) + nLow;
}