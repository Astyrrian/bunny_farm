#include <iostream>
#include "conio.h"
#include <cstdlib>
#include "terrain.h"
#include "farm.h"

using std::cout;
using std::cin;
using std::endl;

//#define SSTR(x) dynamic_cast <std::ostringstream&> (std::ostringstream()<<std::dec<<x).str()

#define FARM_SIZE_X 50
#define FARM_SIZE_Y 50
#define RNG_SEED  3321
#define MAX_RAND_NUM 10000

unsigned int getRandomNumber(int nLow, int nHigh);

int main() {
	//Initialize the random number generator:
	std::srand(RNG_SEED);
	int xSize = 5;
	int ySize = 10;
	while (1) {
		//Generate the farm:
		cout << "Enter X and Y:" ; cin >> xSize >> ySize;
		
		if ((xSize > 0) && (ySize > 0)) {
			int nRand = getRandomNumber(0, MAX_RAND_NUM);
			farm myFarm(nRand, xSize, ySize);
			myFarm.printFarm();
			myFarm.createBunny(NULL,NULL);
			myFarm.printFarm();
			//cout << myFarm.getTile(0,0).strSymbol << endl;
		} else {
			cout << "GOODBYE!" << endl;
			break;
		}
	}
	//farm myFarm(RNG_SEED, xSize, ySize);
	//myFarm.printFarm();
	//cout << myFarm.getSizeX() << " : " << myFarm.getSizeY() << endl;

	_getch();
	return 0;
}


unsigned int getRandomNumber(int nLow, int nHigh) {
	return (rand() % (nHigh - nLow + 1)) + nLow;
}
