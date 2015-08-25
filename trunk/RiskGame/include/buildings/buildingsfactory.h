#ifndef BUILDINGS_FACTORY_H
#define BUILDINGS_FACTORY_H

#include "buildings/building.h"
#include "buildings/bunker.h"
#include "buildings/factory.h"

#include <boost/shared_ptr.hpp>
#include "utils/ids.h"
#include <map>
/**
	Klasa fabryki skalowalnej budynkow w grze
*/
class BuildingsFactory
{
public:
	typedef boost::shared_ptr<Building> pBuilding;
    typedef pBuilding (*createBuildingsFunc)();

    BuildingsFactory();
	/**
		@return instancja fabryki budynkow
	*/
    static BuildingsFactory& getInstance(){
        static BuildingsFactory b;
        return b;
    }

	bool registerFunc(BuildingsId id, createBuildingsFunc func);

    pBuilding create(BuildingsId id);

private:
    typedef std::map<BuildingsId, createBuildingsFunc> Callbacks;

    Callbacks callbacks_;
};

#endif // BUILDINGS_FACTORY_H
