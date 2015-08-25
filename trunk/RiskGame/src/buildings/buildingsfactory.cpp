#include "buildings/buildingsfactory.h"

BuildingsFactory::BuildingsFactory(){

}

bool BuildingsFactory::registerFunc(BuildingsId id, createBuildingsFunc func){
    return callbacks_.insert(std::pair<BuildingsId, createBuildingsFunc>(id, func)).second;
}

BuildingsFactory::pBuilding BuildingsFactory::create(BuildingsId id){
    Callbacks::const_iterator i = callbacks_.find(id);

    if(i == callbacks_.end()){
        //jakoœ zaznaczyæ error trzeba, chocia¿ tu nigdy nie powinniœmy trafiæ - wiêc pewnie raczej assert

        return pBuilding();
    } else {
        return (i->second)();
    }
}