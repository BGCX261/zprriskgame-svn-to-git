#ifndef TANK_H
#define TANK_H

#include "units/unit.h"
#include "units/unitsfactory.h"

/**
	Klasa jednostki czolg
	@see Unit
*/
class Tank : public Unit
{
public:
    Tank(int attack = UNITS_ATTACK[TANK], int defence = UNITS_DEFENCE[TANK],
        int cost = UNITS_COST[TANK], QString name = UNITS_NAME[TANK]) 
        : Unit(attack, defence, cost, name) {}

	/**
		Tworzy nowy czolg
		@return wskaznik na czolg
	*/
	static pUnit create(){
        return pUnit(new Tank());
    }

    virtual UnitsId type() const {return TANK;}
private:
static bool registered_;
};

#endif // TANK_H
