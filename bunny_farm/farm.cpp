/*Main cpp file*/
#include "farm.h"  //Uncomment this when separating header and cpp

#include <iostream>
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
	
	for (int nX = 0; nX < nXSize; ++nX) {
		for (int nY = 0; nY < nYSize; ++nY) {
			myFarm.push_back(myTerrain.genTerrain());
		}
	}

}

tile farm::getTile(const int x, const int y) {
	x = std::max(0,std::min(x,nXSize));
	y = std::max(0,std::min(y,nYSize));
	return myFarm[y*nXSize+x];
}

void farm::printFarm() {

	cout << endl;
	for (int nY = 0; nY < nYSize; ++nY) {
		cout << "      " ;
		for (int nX = 0; nX < nXSize; ++nX) {
			cout << myFarm[nY*nXSize+nX].strSymbol ;
		}
		cout << endl;
	}
	cout << endl;
}

unsigned int farm::getRandomNumber(const int nLow, const int nHigh) {
	return (rand() % (nHigh - nLow + 1)) + nLow;
}
