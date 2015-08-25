#ifndef OWNERRAPORT_H
#define OWNERRAPORT_H

#include "raports/raport.h"
#include "raports/raportfactory.h"

/**
	Klasa reprezentujaca raport ze zmian wlasciciela terytorium
	@see Raport
	@see Calculator
*/
class OwnerRaport : public Raport{
public:
	/**
		Kontruktor
		@param terrId identyfikator terytorium ktorego dotyczy raport
		@param from id zawodnika ktory byl pierwotnym wlascicielem
		@param to id zawodnika ktory zostaje nowym wlasicielem
	*/
	OwnerRaport(int terrId, PlayerId from, PlayerId to);

    static pRaport create(int terrId, int from, int to, int dummy){
        dummy = 1;
        if(dummy==1)
            dummy++;
        return pRaport(new OwnerRaport(terrId, PlayerId(from), PlayerId(to)));
    }

	virtual int type(){
		return RaportsId(OWNERSHIP);
	}
	/**
		@return identyfikator terytorium ktorego dotyczy raport
	*/
	int getTerritoryId(){ return terrId_; }
	/**
		@return id zawodnika ktory byl pierwotnym wlascicielem
	*/
	PlayerId getFromPlayer(){ return fromPlayer_; }
	/**
		@return id zawodnika ktory zostaje nowym wlasicielem
	*/
	PlayerId getToPlayer(){ return toPlayer_; }

private:
    int terrId_;
    PlayerId fromPlayer_;
    PlayerId toPlayer_;

    static bool registered_;
};

#endif
