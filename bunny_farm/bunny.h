#ifndef __BUNNY_H
#define __BUNNY_H
//TODO: Turn this class into a subclass of a critter class so we can create other animals

#include <string>
#include <vector>
//#include "tile.h"
//#include "terrain.h"
//#include "farm.h"

using std::string;


class bunny {
private:
	string strName;
	string strGender;
	int nAge;
	int nBirthYear;

	bunny* pMother;
	bunny* pFather;
	std::vector<bunny*> pOffSprings;
	int nNumOffSprings;
	string strSymbol;
	//statuses:
	bool bDead;
	string strCauseOfDeath;
	int nXCoord;
	int nYCoord;

	//private methods:
	//unsigned int getRandomNumber(int , int ); 
	
	bunny(); //default constructor
	

public:
	//~bunny(); //destructor
	bunny(const string strNewName, const string strNewGender,\
		bunny *pNewMother, bunny *pNewFather, const int nYear);
	
	//Getters:
	string getName() { return strName; }
	string getGender()  { return strGender; }
	int    getAge()  { return nAge; }
	bunny* getMother() { return pMother; }
	bunny* getFather() { return pFather; }
	std::vector<bunny*> getOffSprings() { return pOffSprings; }
	int    getNumOffSprings() { return nNumOffSprings; }
	bool   isDead()  { return bDead; }
	string getCauseOfDeath() { return strCauseOfDeath; }
	string getSymbol() { return strSymbol;}
	int    getBirthYear() { return nBirthYear; }
	void   getLocation(int *pnX, int *pnY);
	
	//Setters:
	void setSymbol(string strNSym) { strSymbol = strNSym; }
	void setLoc(const int nX, const int nY);

	//Other methods:
	void kill(const string strCause);
	void age();
	void addOffSpring(bunny* pNewOffSpring);
	
	bool checkAgeDeath(const double c, const double n, const int nCheckNum);
	
//bunny deathrate function:
// int probabilityOfDeath = 1/(1+e^(-c*(x-n))) * 1000
// where int n = the 50% chance threshold
// int x is the age
// and float c = the sharpness of the probabilistic curve. Smaller c means flatter curve.
// multiply by 1000 to normalize between 0 and 1000
// for n = 13 and c = 0.44. The probability of death (p) and the cumulative probability to survive to age (cp):
// The probabilities are out of 1000
//  x = 1, p = 5,  cp = 992
//  x = 2, p = 8, cp = 984
//  x = 5, p = 29, cp = 926
//  x = 10, p = 211, cp = 501
//  x = 15, p = 707, cp = 42
//  x = 30, p = 999, cp = 0


};

#endif
