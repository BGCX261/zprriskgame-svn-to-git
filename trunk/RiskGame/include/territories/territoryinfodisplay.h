#ifndef TERRITORYINFODISPLAY_H
#define TERRITORYINFODISPLAY_H

#include "territories/territory.h"
#include "utils/defs.h"

#include <QLabel>

/**
	Klasa wyswietlania info o danym terenie
*/
class TerritoryInfoDisplay : public QLabel
{
public:
	/**
		Konstruktor
		@param parent rodzic widgetu
	*/
    TerritoryInfoDisplay(QWidget* parent = 0)
        : QLabel(parent) {}
	/**
		pokazuje informacje o terytorium
		@param id identyfikator terenu o ktorym chcemy pokazac informacje
	*/
    void showTerritoryInfo(int id);
	/**
		ukrywa informacje o terytorium
	*/
    void hideTerritoryInfo();
};

#endif // TERRITORYINFODISPLAY_H
