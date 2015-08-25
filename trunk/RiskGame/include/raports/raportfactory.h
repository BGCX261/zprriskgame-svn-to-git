#ifndef RAPORTFACTORY_H
#define RAPORTFACTORY_H

#include "raports/raport.h"
#include "raports/battleraport.h"
#include "raports/objectraport.h"
#include "raports/ownerraport.h"
/**
	Klasa fabryki skalowalnej raportow po zakonczonej turze
*/
class RaportFactory {
public:
    RaportFactory() {};

    typedef pRaport (*createRaportsFunc)(int par1, int par2, int par3, int par4);

	/**
		@return instancja fabryki raportow
	*/
    static RaportFactory& getInstance(){
        static RaportFactory f;
        return f;
    }

    bool registerFunc(RaportsId id, createRaportsFunc func);

    pRaport create(RaportsId id, int par1, int par2, int par3, int par4);

private:
    typedef std::map<RaportsId, createRaportsFunc> Callbacks;
    Callbacks callbacks_;


};
#endif