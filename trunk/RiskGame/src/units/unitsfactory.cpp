#include "units/unitsfactory.h"

UnitsFactory::UnitsFactory(){

}

bool UnitsFactory::registerFunc(UnitsId id, createUnitsFunc func){
    return callbacks_.insert(std::pair<UnitsId, createUnitsFunc>(id, func)).second;
}

UnitsFactory::pUnit UnitsFactory::create(UnitsId id){
    Callbacks::const_iterator i = callbacks_.find(id);

    if(i == callbacks_.end()){
        //jako� zaznaczy� error trzeba, chocia� tu nigdy nie powinni�my trafi� - wi�c pewnie raczej assert

        return pUnit();
    } else {
        return (i->second)();
    }
}