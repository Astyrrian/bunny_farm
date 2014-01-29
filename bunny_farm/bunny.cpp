/*start implementation file*/
#include "bunny.h" //Uncomment when splitting
#include <math.h>

bunny::bunny(const string strNewName, const string strNewGender,\
	bunny *pNewMother, bunny *pNewFather, const int nYear)
	: strName(strNewName), strGender(strNewGender), pMother(pNewMother), pFather(pNewFather), nBirthYear(nYear) {
	bDead = false;
	strCauseOfDeath = "";
	nAge = 0;
	nNumOffSprings = 0;
	if (strNewGender == "male") {
		strSymbol = "B";
	} else {
		strSymbol = "b";
	}
}

void bunny::setLoc(const int nX, const int nY){
	nXCoord = nX;
	nYCoord = nY;
}

void  bunny::getLocation(int *pnX, int *pnY) {
	(*pnX) = nXCoord;
	(*pnY) = nYCoord;
}

void bunny::addOffSpring(bunny* pNewOffSpring){
	nNumOffSprings++;
	pOffSprings.push_back(pNewOffSpring);
}

void bunny::kill (const string strCause) { 
	strCauseOfDeath = strCause; 
	bDead = true; 
	nXCoord = -1;
	nYCoord = -1;
}

void bunny::age() {
	if (!bDead) {
		nAge++;
	}
}

bool bunny::checkAgeDeath(const double c, const double n, const int nCheckNum) {
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
	unsigned int nProbabilityOfDeath = static_cast<unsigned int>(1000.0/(1.0+exp(-c*(nAge-n))));
	return (nCheckNum<=nProbabilityOfDeath);
}

