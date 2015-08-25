#include "raports/raportfactory.h"


bool RaportFactory::registerFunc(RaportsId id, createRaportsFunc func){
    return callbacks_.insert(std::pair<RaportsId, createRaportsFunc>(id, func)).second;
}

pRaport RaportFactory::create(RaportsId id, int par1, int par2, int par3, int par4){
    Callbacks::const_iterator i = callbacks_.find(id);

    if(i == callbacks_.end()){
        //jakoœ zaznaczyæ error trzeba, chocia¿ tu nigdy nie powinniœmy trafiæ - wiêc pewnie raczej assert

        return pRaport();
    } else {
        return (i->second)(par1, par2, par3, par4);
    }
}

