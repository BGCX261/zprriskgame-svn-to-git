#ifndef OTHER_H
#define OTHER_H

#include "utils/ids.h"
#include "utils/defs.h"
#include "utils/constants.h"

int calculateAttack(UnitsMap& m);
int calculateDefence(UnitsMap& m);
void removeUnit(UnitsMap& m, int n);
int noUnits(UnitsMap& m);

int combineInts(int a, int b);
int getFirstCombined(int val);
int getSecondCombined(int val);

#endif