#ifndef OBJECTRAPORT_H
#define OBJECTRAPORT_H

#include "raports/raport.h"
#include "raports/raportfactory.h"

/**
	Klasa reprezentujaca raport budowy lub rektutacji
	@see Raport
	@see Calculator
*/
class ObjectRaport : public Raport{
public:
	/**
		Konstruktor
		@param buildId identyfikuje czy chodzi o budynek czy jednostke
		@param ter identyfikator terytorium ktorego dotyczy raport
		@param objId identyfikator obiektu
		@param noObj liczba obiektow
	*/
	ObjectRaport(BuildId buildId, int ter, int objId, int noObj);

    static pRaport create(int buildId, int ter, int objId, int noObj){
        return pRaport(new ObjectRaport(BuildId(buildId), ter, objId, noObj));
    }

	virtual int type(){
		return RaportsId(OBJECT);
	}
	/**
		@return identyfikator terytorium ktorego dotyczy raport
	*/
	int getTerritoryId(){ return terrId_; }
	/**
		@return czy chodzi o budynek czy jednostke
	*/
	BuildId getBuildId(){ return buildId_; }
	/**
		@return identyfikator obiektu
	*/
	int getObjectId(){ return objectId_; }
	/**
		@return liczba obiektow
	*/
	int getNoObjects(){ return noObjects_; }

private:
    int terrId_;
    BuildId buildId_;
    int objectId_;
    int noObjects_;
	static bool registered_;
};

#endif
