#ifndef BUILDING_H
#define BUILDING_H

#include "utils/ids.h"
#include "utils/defs.h"
#include "utils/constants.h"

#include <boost/shared_ptr.hpp>
#include <QString>

/**
	Klasa bazowa dla budynkow na planszy
*/
class Building
{
public:
/**
	Konstruktor
	@param cost koszt budynku
	@param name nazwa bydynku
*/
	Building(int cost, QString name)
		: cost_(cost)
		, name_(name) {}

	virtual BuildingsId type() const = 0;
/**
	@return koszt budynku
*/
	int cost() const {return cost_;}
/**
	@nazwa budynku
*/
	QString name() const {return name_;}
private:
	int const cost_;
	QString const name_;
};

#endif // BUILDING_H
