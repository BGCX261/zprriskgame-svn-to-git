#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "utils/defs.h"
#include "utils/other.h"
#include "raports/raport.h"
#include "raports/battleraport.h"
#include "raports/objectraport.h"
#include "raports/ownerraport.h"
#include "utils/filelogger.h"
#include "map.h"

/**
	Klasa interpretujaca raporty
	@see Raport
*/
class Interpreter {
public:

    typedef shared_ptr<BattleRaport> pBRaport;
    typedef shared_ptr<ObjectRaport> pObRaport;
    typedef shared_ptr<OwnerRaport> pOwRaport;

    typedef QVector<pBRaport> bVect;
    typedef QVector<pObRaport> obVect;
    typedef QVector<pOwRaport> owVect;

    Interpreter();
	/**
		@return instancja interpretera
	*/
    static Interpreter& getInstance(){
        static Interpreter i;
        return i;
    }
	/**
		uaktualnia rozgrywke zgodnie z raportem
		@param v wektor raportow
	*/
    void applyRaports(raportVect v);
    
	/**
		@return informacje o przebiegu rozgrywki ktorej dotyczyl ostatni raport
	*/
    stringVect info();
private:

    void clear();
    void write(QString s);
    void separateRaports(raportVect& v);

    void applyObjectRaports();
    void applyBattleRaports();
    void applyOwnerRaports();
    void calculateMoney();

    bVect battleRaports_;
    obVect objectRaports_;
    owVect ownerRaports_;
    stringVect info_;
    Map& map_;
};

#endif