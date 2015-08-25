#ifndef UNITS_FACTORY_H
#define UNITS_FACTORY_H

#include "units/unit.h"
#include "units/infantry.h"
#include "units/tank.h"

#include <boost/shared_ptr.hpp>
#include "utils/ids.h"
#include <map>
/**
	Klasa fabryki skalowalnej jednostek w grze
*/
class UnitsFactory
{
public:
	typedef boost::shared_ptr<Unit> pUnit;
    typedef pUnit (*createUnitsFunc)();

    UnitsFactory();
	/**
		@return instancja fabryki jednostek
	*/
    static UnitsFactory& getInstance(){
        static UnitsFactory f;
        return f;
    }

	bool registerFunc(UnitsId id, createUnitsFunc func);

    pUnit create(UnitsId id);

private:
    typedef std::map<UnitsId, createUnitsFunc> Callbacks;

    Callbacks callbacks_;
};

#endif // UNITS_FACTORY_H
