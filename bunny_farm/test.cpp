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
		"dirt", \
		"grass", \
		"rock", \
		"water", \
		"hole", \
		"lava" \
	};
	
	static const int nTerrainTypeSize = astrTerrainType.size();

	string getTerrain(int nTerrainNum) {
		if (nTerrainNum >= nTerrainTypeSize) {
			return "INVALID";
		} else {
			return astrTerrainType[nTerrainNum];
		} 
	}

};

//void printFarm (

int main() {
	//Initialize the random number generator:
	std::srand(RNG_SEED);
	//Generate the farm:
	/*farm[FARM_SIZE_X][FARM_SIZE_Y] myFarm;

	for (int nX = 0; nX < FARM_SIZE_X; ++nX) {
		for (int nY = 0; nY < FARM_SIZE_Y; ++nY) {
		*/
	cout << "Enter an integer" << endl;
	int input;
	cin >> input;
	cout << terrains::getTerrain(input) << endl;

	_getch();
	return 0;
}
