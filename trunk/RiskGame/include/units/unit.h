#ifndef UNIT_H
#define UNIT_H

#include "utils/ids.h"
#include "utils/defs.h"
#include "utils/constants.h"

#include <boost/shared_ptr.hpp>
#include <QString>
/**
	Klasa bazowa dla jednostek
*/
class Unit
{
public:
	/**
	Konstruktor
	@param attack wartosc ataku
	@param defense ilosc punktow obrony
	@param cost koszt rekrutacji
	@param name nazwa jednostki
	@param noUnits liczba jednostek
	*/
    Unit(int attack, int defence, int cost, QString name, int noUnits = 1)
        : attack_(attack)
        , defence_(defence)
        , cost_(cost)
        , noUnits_(noUnits)
        , name_(name){}

    void addUnit(int n = 1) {noUnits_+=n;}
    void removeUnit(int n = 1) {noUnits_-=n; if(noUnits_<0) noUnits_=0;}
    void setNoUnits(int noUnits) {noUnits_ = noUnits;}

    virtual UnitsId type() const = 0;

	/**
		@return wartosc ataku
	*/
    int attack() const {return attack_;}
	/**
		@return ilosc punktow obrony
	*/
    int defence() const {return defence_;}
	/**
		@return koszt rekrutacji
	*/
    int cost() const {return cost_;}
	/**
		@return nazwa jednostki
	*/
    QString name() const {return name_;}
	/**
		@return liczba jednostek
	*/
    int noUnits() const {return noUnits_;}

private:
    int const attack_;
    int const defence_;
    int const cost_;
    QString const name_;
    int noUnits_;
};

#endif // UNIT_H
