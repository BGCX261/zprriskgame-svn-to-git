#ifndef WATCHTOWER_H
#define WATCHTOWER_H

#include "buildings/building.h"
#include "buildings/buildingsfactory.h"

/**
	Klasa budynku wiezy obserwacyjnej
	@see Building
*/
class Watchtower : public Building
{
public:
    Watchtower(int cost = BUILDINGS_COST[WATCHTOWER],
        QString name=BUILDINGS_NAME[WATCHTOWER])
		: Building(cost, name) {}
	
	/**
		Tworzy nowa wieze
		@return wskaznik na wieze
	*/
	static pBuilding create(){
        return pBuilding(new Watchtower());
    }

    virtual BuildingsId type() const {return WATCHTOWER;}

private:
static bool registered_;
};

#endif //
