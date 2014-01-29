/*Main cpp file*/
#include "farm.h"  //Uncomment this when separating header and cpp

#include <fstream>
#include <iostream>
#include <ctype.h>
#include <algorithm>

#define FEMALE_NAME_TEXT_FILE "../data/texts/female-names.txt"
#define MALE_NAME_TEXT_FILE "../data/texts/male-names.txt"

#define NUM_NAME_GEN_TRIES 1000
#define MAX_NUM_BUNNIES 5000
#define C_CONSTANT 0.44
#define N_CONSTANT 13

using std::cout;
using std::endl;

void farm::simTurn() {
	
	// 1) Update year and age
	// 2) Kill Bunnies of old age
	updateAge(); //This does 1) and 2)
	// TODO still
	// 3) Move Wolves
	// 4) Kill Bunnies who are eaten
	
	// 5) Move Bunnies
	// 6) Kill Bunnies who fall into Lava
	for (unsigned int cnt = 0; cnt < vBunnyList.size(); ++cnt) {
		moveBunny(&vBunnyList[cnt]); //This does both 5) and 6)
	}

	// 7) Reproduce <3 <3
	//cout << "DEBUG: Ending simTurn()" << endl;
}
/*
farm::~farm() {
	delete &vBunnyList;
	delete &hBunnyName;
	delete &vstrMaleNames;
	delete &vstrFemaleNames;
	delete &myFarm;
}*/

farm::farm() {
	nRNG_SEED = 0;
	nXSize = 10;
	nYSize = 10;
	myTerrain.setSeed(nRNG_SEED);
	generateSettings();
}

farm::farm(const int nSeed) {
	nRNG_SEED = nSeed;
	nXSize = 10;
	nYSize = 10;
	myTerrain.setSeed(nRNG_SEED);
	generateSettings();
}

farm::farm(const int nX, const int nY) {
	nRNG_SEED = 0;
	nXSize = nX;
	nYSize = nY;
	myTerrain.setSeed(nRNG_SEED);
	generateSettings();
}

farm::farm(const int nSeed, const int nX, const int nY) {
	nRNG_SEED = nSeed;
	nXSize = nX;
	nYSize = nY;
	myTerrain.setSeed(nRNG_SEED);
	generateSettings();
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
	nYear = 0;
}

void farm::generateSettings() {

	vBunnyList.reserve(MAX_NUM_BUNNIES);
	generateFarm();
	nYear = 0;
	vstrMaleNames = generateNames(MALE_NAME_TEXT_FILE);
	vstrFemaleNames = generateNames(FEMALE_NAME_TEXT_FILE);
}

string farm::namifyString (const string strString) {
	string strTemp;
	char c;
	for (unsigned int i=1; i<strString.length(); i++) {
		c=strString[i];
		strTemp.push_back((char)tolower(c));
	}
	strTemp[0] = ((char)toupper(strTemp[0]));
	return strTemp;
}

std::vector<string> farm::generateNames(const string filename) {
	std::vector<string> vstrTemp;
	std::ifstream in_fh(filename.c_str());	
	if (in_fh.is_open()) {
		std::string line;
		while (getline(in_fh,line)) {
			//Capitalize only the first letter:
			vstrTemp.push_back(namifyString(line)); //line;
		}
		in_fh.close();
	} else {
		std::cerr << "Cannot open file: " << filename << endl;
	}
	return vstrTemp;
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
				//cout << "DEBUG: (printFarm) Size of vBunnyList: " << vBunnyList.size() << endl;
				//cout << "DEBUG: (printFarm) Capacity of vBunnyList: " << vBunnyList.capacity() << endl;
				//cout << "DEBUG: (printFarm) Address of vBunnyList is: " << &vBunnyList << endl;
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
	if (!moveableLocation(nXLoc, nYLoc)) {
		return false;
	} else {
		if (myFarm[mapIndex(nXLoc,nYLoc)].bFatal) {
			return false;
		}
	}
	return true;
}

bool farm::moveableLocation(const int nXLoc, const int nYLoc) {
	if ((nXLoc < 0) || (nYLoc < 0) || (nXLoc >= nXSize) || (nYLoc >= nYSize)) {
		//Check boundary conditions
		return false;
	} else {
		//Check valid creation location:
		if (  (myFarm[mapIndex(nXLoc,nYLoc)].bOccupied) || \
			 !(myFarm[mapIndex(nXLoc,nYLoc)].bPassable)    ) {
				return false;
		}
	}
	return true;
}

void farm::moveBunny(bunny *pBunny) {
	if (pBunny->isDead()) { return; }
	//cout << "DEBUG: Moving Bunny " << pBunny->getName() << endl;
	int nXLoc, nYLoc;
	pBunny->getLocation(&nXLoc, &nYLoc);
	//Check adjecent squares for valid moves:
	/*bool abValid[2][2];
	for (int nTempX=0; nTempX <= 2; ++nTempX) {
		for (int nTempY=0; nTempY <= 2; ++nTempY) {
			//By iterating through 0,1,2 for Y, we check the immediate surounding of the bunny
			//(1,1) means current position, (0,1) means one tile to the left. etc.
			if ((nTempX==1)&&(nTempY==1)) {
				abValid[1][1] = true; //No move is an always valid move
			} else {
				abValid[nTempX][nTempY] = moveableLocation(nXLoc+nTempX-1,nYLoc+nTempY-1);
				
			}
		}
	}*/
	int nMoveX = getRandomNumber(-1,1);
	int nMoveY = getRandomNumber(-1,1);
	bool bMoved = true;
	//cout << "DEBUG: Moving Bunny " << pBunny->getName() << endl;
	while(!moveableLocation(nXLoc+nMoveX, nYLoc+nMoveY)) {
		//Not moving is always a move:
		if ((nMoveX==0)&&(nMoveY==0)) {
			bMoved = false;
			break;
		}
		nMoveX = getRandomNumber(-1,1);
		nMoveY = getRandomNumber(-1,1);
	}

	if(bMoved) {
		//If there was a move. (If there wasn't, do nothing)
		int nNewXLoc = nXLoc+nMoveX;
		int nNewYLoc = nYLoc+nMoveY;
		//Update the move:
		updateMove(pBunny, nNewXLoc, nNewYLoc);

	}

}

void farm::updateMove(bunny *pBunny, const int nNewXLoc /*=-1*/, const int nNewYLoc/*=-1*/) {
	//To remove a bunny from the farm (e.i. when they die), this is signified by nNewXLoc or nNewYLoc <= -1
	//Which is the default value
	//First, update the tile:
	int  nXLoc, nYLoc;
	pBunny->getLocation(&nXLoc, &nYLoc);
	myFarm[mapIndex(nXLoc,nYLoc)].bOccupied = false;
	myFarm[mapIndex(nXLoc,nYLoc)].pBunny = NULL;
	if ((nNewXLoc >= 0) && (nNewYLoc >= 0)) {
		//Check to see if it stepped on a fatal square:
		if (myFarm[mapIndex(nNewXLoc, nNewYLoc)].bFatal) {
			string strDeathReason = "fell into a "+myFarm[mapIndex(nNewXLoc, nNewYLoc)].strName+" square";
			cout << "The bunny " << pBunny->getName() << " " << strDeathReason << " at the age of " << pBunny->getAge() << "..." << endl;
			killBunny(pBunny,strDeathReason);
		} else {
			myFarm[mapIndex(nNewXLoc,nNewYLoc)].bOccupied = true;
			myFarm[mapIndex(nNewXLoc,nNewYLoc)].pBunny = pBunny;
			//Then update the bunny's location tracker:
			pBunny->setLoc(nNewXLoc, nNewYLoc);
		}
	} else {
		nEmptyTiles++;
	}
}

bool farm::createBunny(bunny *pNewMother, bunny *pNewFather, const int nXLoc /*= -1*/, const int nYLoc /*= -1*/) {
	//The pNewMother and pNewFather pointers are pointers to the parents of the new bunny. If they are null, then it means 
	//They are the initial bunnies
	//creates a bunny object with age 0, at (nXLoc, nYLoc). If (nXLoc, nYLoc) is less than -1, then the placement is random
	//if any of the X or Y location is greater than the size of the farm, then the placement is random
	//Bunnys will not be created on any fatal or inpassable tiles nor will it be placed on an occupied tile
	if (nEmptyTiles <= 0) {
		//No empty tiles
//		cout << "DEBUG: createBunny - No Empty Tiles" << endl;
		return false;
	}
	if (vBunnyList.size() >= MAX_NUM_BUNNIES) {
		//Max # of bunnies reached
		return false;
	}
	int nX = nXLoc;
	int nY = nYLoc;
	//cout << "DEBUG: createBunny - Pre validLocation()" << endl;
	int cnt = 0;
	while (!validLocation(nX,nY)) {
		nX = getRandomNumber(0,nXSize);
		nY = getRandomNumber(0,nYSize);
		if (cnt >= 1000) {
			return false;
		}
	}
	//cout << "DEBUG: createBunny - Post validLocation()" << endl;

	//Generate the gender:
	string strGender;
	if (getRandomNumber(0,1) == 0) {
		strGender = "female";
	} else {
		strGender = "male";
	}
	//Random name function:
	string strBName = genBunnyName(strGender);
	
	//check the name hash for valid name:
	int count = 0;
	while (hBunnyName.count(strBName) == 1) {
		if (count >= NUM_NAME_GEN_TRIES) {
			return false;
		}
		//generate new names
		strBName = genBunnyName(strGender);
		count++;		
	}
	
	//Create the new Bunny
	vBunnyList.push_back(bunny(strBName, strGender, pNewMother, pNewFather, nYear));
	//if the bunny's parents exists, update their OffSprings
	if (pNewMother!=NULL) {
		pNewMother->addOffSpring(&(vBunnyList.back()));
	}
	if (pNewFather!=NULL) {
		pNewFather->addOffSpring(&(vBunnyList.back()));
	}
	//Update the bunny name hash:
	hBunnyName[strBName] = &(vBunnyList.back());
	if (strGender == "male") {
		vMaleAliveBunnies.push_back(&(vBunnyList.back()));
	} else {
		vFemaleAliveBunnies.push_back(&(vBunnyList.back()));
	}
	//Update the farm variables:
	nEmptyTiles--;
	myFarm[mapIndex(nX,nY)].bOccupied = true;
	myFarm[mapIndex(nX,nY)].pBunny = &(vBunnyList.back());
	myFarm[mapIndex(nX,nY)].pBunny->setLoc(nX,nY);
	cout << "A new " << strGender << " bunny, " << strBName << ", was born!" << endl;
	//cout << "DEBUG: Size of vBunnyList: " << vBunnyList.size() << endl;
	//cout << "DEBUG: Capacity of vBunnyList: " << vBunnyList.capacity() << endl;
	//cout << "DEBUG: Address of vBunnyList is: " << &vBunnyList << endl;
	return true;
}



string farm::genBunnyName(string strGender) {
	if ( strGender == "male" ) {
		int nNameSize = vstrMaleNames.size();
		return vstrMaleNames[getRandomNumber(0,nNameSize-1)];
	} else {
		int nNameSize = vstrFemaleNames.size();
		return vstrFemaleNames[getRandomNumber(0,nNameSize-1)];
	}
}

void farm::updateAge() {
	nYear++;
	cout << "\tStart of year " << nYear << endl;
	for (std::vector<bunny>::iterator it = vBunnyList.begin() ; it != vBunnyList.end(); ++it) {
		if (it->isDead()) { continue; } //Dead bunnies don't age.
		it->age();
		//TODO: Check the age and see if it dies of old age. If it does, then it->kill("Old Age")
		//To test:
		if (it->checkAgeDeath(C_CONSTANT,N_CONSTANT, getRandomNumber(0, 1000))) {
			//dies
			string strDeathReason = "old age";
			killBunny(&(*it),strDeathReason);
			cout << "The bunny " << it->getName() << " dies due to old age at the age of " << it->getAge() << " years old..." << endl;
		} else {
			cout << "The bunny " << it->getName() << " is now " << it->getAge() << " years old!" << endl;
		}
	}

}

void farm::killBunny(bunny *pBunny, const string strReason) {
	//Update the AliveBunnies vector
	if (pBunny->getGender() == "male") {
		vstrMaleNames.erase(std::find(vstrMaleNames.begin(), vstrMaleNames.end(), &pBunny));
	} else { 
		vstrFemaleNames.erase(std::find(vstrFemaleNames.begin(), vstrFemaleNames.end(), &pBunny));
	}
	
	//Change the tile settings:
	updateMove(pBunny);
	//Then kill the bunny
	pBunny->kill(strReason);
}