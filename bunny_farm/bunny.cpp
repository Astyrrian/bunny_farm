/*start implementation file*/
#include "bunny.h" //Uncomment when splitting


bunny::bunny(const string strNewName, const bool bNewMale,\
	bunny *pNewMother, bunny *pNewFather)
	: strName(strNewName), bMale(bNewMale), pMother(pNewMother), pFather(pNewFather) {
	bDead = false;
	strCauseOfDeath = "";
	nAge = 0;
	nNumOffSprings = 0;
	if (bNewMale) {
		strSymbol = "B";
	} else {
		strSymbol = "b";
	}
}

void bunny::addOffSpring(bunny* pNewOffSpring){
	nNumOffSprings++;
	pOffSprings.push_back(pNewOffSpring);
}

void bunny::kill (const string strCause) { 
	strCauseOfDeath = strCause; 
	bDead = true; 
}

void bunny::age() {
	if (!bDead) {
		nAge++;
	}
}