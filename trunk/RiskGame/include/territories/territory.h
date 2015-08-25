#ifndef TERRITORY_H
#define TERRITORY_H

#include "buildings/building.h"
#include "buildings/watchtower.h"
#include "buildings/bunker.h"
#include "buildings/factory.h"
#include "buildings/buildingsfactory.h"
#include "units/unit.h"
#include "units/infantry.h"
#include "units/tank.h"
#include "units/unitsfactory.h"
#include "utils/ids.h"
#include "utils/defs.h"
#include "player/player.h"
#include "map.h"
#include "utils/defs.h"

#include <QVector>

#include <QPoint>
#include <QString>

#include <boost/shared_ptr.hpp>

class Player;
/**
	Klasa reprezentujaca terytorium na mapie
*/
class Territory
{
public:
	/**
		Konstruktor
		@param points wektor punktow z ktorych tworzona jest granica terytorium
		@param name nazwa terytorium
		@param neighbours wektor identyfikatorow sasiadow
		@param id identyfikator terytorium
	*/
    Territory(pointVect points, QString name, idVect neighbours, int id);

	/**
		Pozwala uzyskac jednostki utrzymywane na terytorium
		@return units_ wektor jednostek
	*/
    unitVect units() {return units_;}
	/**
		dodaje jednostki do terytorium
		@param id identyfikator jednostki
		@param noUnits liczba jednostek
	*/
    void addUnit(UnitsId id, int noUnits = 1);
	/**
		usuwa jednostki z terytorium
		@param id identyfikator jednostki
		@param noUnits liczba jednostek
	*/
    void removeUnit(UnitsId id, int noUnits = 1);
	/**
		ustawia jednostki na terytorium
		@param id identyfikator jednostki
		@param noUnits liczba jednostek
	*/
    void setUnit(UnitsId id, int noUnits = 1);

	/**
		dodaje budynek do terytorium
		@param id identyfikator budynku
	*/
    void addBuilding(BuildingsId id);
	/**
		dodaje budynek do terytorium
		@param b wkaznik na obiekt budynku
	*/
    void addBuilding(pBuilding b) {buildings_.push_back(b);}

	/**
		@return punkty graniczne terytorium
	*/
    pointVect getPoints() const {
        return points_;
    }

	/**
		Metoda okresla kto jest wlascicielem terytorium
		@return id wlasciciela
	*/
    PlayerId ownership() {return ownership_;}
    void setOwnership(PlayerId ownership) { ownership_ = ownership;}
	
	/**
		@return identyfikator terytorium
	*/
    int id() const {return id_;}
	
	/**
		@return srodek terytorium
	*/
    QPoint getCenter();

	/**
		Okresla czy terytorium jest sasiadem terytorium o danym id
		@param id identyfikator terytorium ktorego sasiedztwo badamy
		@return czy jest
	*/
    bool isNeighbour(int id); 

	/**
		@return nazwa terytorium
	*/
    QString name() const {return name_;}

	/**
		@return liczba jednostek stacjonujacych na terytorium
	*/
    int noUnits() const;
	/**
		@param id identyfikator jednostki
		@return libcza jednostek terytorium o danym id
	*/
    int noUnits(UnitsId id);
    int noUnitsTypes() const;

	/**
		Metoda okreslajaca czy terytorium posiada dany typ budynku
		@param id identyfikator budynku
		@return czy posiada
	*/
    bool hasBuilding(BuildingsId id) const;

	/**
		Czy terytorium jest widoczne czy zasloniete mgla wojny
		@return czy widoczne
	*/
    bool isVisible() const;

	/**
		@return bonus defensywny terytorium
	*/
    int getDefenseBonus() const;
	/**
		@return bonus ekonomiczny terytorium
	*/
    int getEconomyBonus() const;

#ifdef TESTS
    void clearUnits() {units_.clear();}
    void clearBuildings() {buildings_.clear();}
#endif

private:
    pUnit getUnit(UnitsId id);

    pointVect points_;      // wspó³rzêdny rogów na mapie
    buildingVect buildings_;// lista budynków
    unitVect units_;        // lista jednostek
    idVect neighbours_;     // lista id s¹siadów

    const QString name_;    // nazwa - w stylu Sahara
    PlayerId ownership_;   // do kogo nale¿y pole - neutralny, player1 (serwer), player2
    const int id_;          // unikalne id

};

#endif // TERRITORY_H
