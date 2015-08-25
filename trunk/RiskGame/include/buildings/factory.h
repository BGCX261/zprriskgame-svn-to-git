#ifndef FACTORY_H
#define FACTORY_H

#include "buildings/building.h"
#include "buildings/buildingsfactory.h"

/**
	Klasa budynku fabryki
	@see Building
*/
class Factory : public Building
{
public:
    Factory(int cost = BUILDINGS_COST[FACTORY],
        QString name=BUILDINGS_NAME[FACTORY])
		: Building(cost, name) {}
	
	/**
		Tworzy nowa fabruke
		@return wskaznik na fabryke
	*/
	static pBuilding create(){
		return pBuilding(new Factory());
    }

	/**
		Metoda podaje bonus ekonomiczny
		@return wartosc bonusu
	*/
	int getEconomyBonus() { return FACTORY_BONUS; }

    virtual BuildingsId type() const {return FACTORY;}
	
private:
	static bool registered_;
};

#endif // FACTORY_H
