#ifndef INFANTRY_H
#define INFANTRY_H

#include "units/unit.h"
#include "units/unitsfactory.h"

/**
	Klasa jednostki piechoty
	@see Unit
*/
class Infantry : public Unit
{
public:
    Infantry(int attack = UNITS_ATTACK[INFANTRY], int defence = UNITS_DEFENCE[INFANTRY],
        int cost = UNITS_COST[INFANTRY], QString name = UNITS_NAME[INFANTRY])
        : Unit(attack, defence, cost, name) {}

	/**
		Tworzy nowa jednostke piechoty
		@return wskaznik na piechote
	*/
	static pUnit create(){
        return pUnit(new Infantry());
    }

    virtual UnitsId type() const {return INFANTRY;}
private:
static bool registered_;
};

#endif // INFANTRY_H
