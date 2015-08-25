#include "units/unitsfactory.h"

UnitsFactory::UnitsFactory(){

}

bool UnitsFactory::registerFunc(UnitsId id, createUnitsFunc func){
    return callbacks_.insert(std::pair<UnitsId, createUnitsFunc>(id, func)).second;
}

UnitsFactory::pUnit UnitsFactory::create(UnitsId id){
    Callbacks::const_iterator i = callbacks_.find(id);

    if(i == callbacks_.end()){
        //jakoœ zaznaczyæ error trzeba, chocia¿ tu nigdy nie powinniœmy trafiæ - wiêc pewnie raczej assert

        return pUnit();
    } else {
        return (i->second)();
    }
}