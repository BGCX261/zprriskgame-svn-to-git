#ifndef BUNKER_H
#define BUNKER_H

#include "buildings/building.h"
#include "buildings/buildingsfactory.h"

/**
	Klasa budynku bunkra
	@see Unit
*/
class Bunker : public Building
{
public:
    Bunker(int cost = BUILDINGS_COST[BUNKER],
        QString name=BUILDINGS_NAME[BUNKER])
		: Building(cost, name) {}
	
	/**
		Tworzy nowy bunkier
		@return wskaznik na bunkier
	*/
	static pBuilding create(){
		return pBuilding(new Bunker());
    }
	/**
		Metoda podaje bonus przy obronie
		@return wartosc bonusu
	*/
	int getDefenseBonus() { return BUNKER_BONUS; }

    virtual BuildingsId type() const {return BUNKER;}
	
private:
static bool registered_;
};

#endif // BUNKER_H
