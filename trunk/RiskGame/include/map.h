#ifndef MAP_H
#define MAP_H

#include "territories/territory.h"
#include "utils/defs.h"

#include <QtCore/QCoreApplication>
#include <QtXml>
#include <QString>
#include <QFile>
#include <Qt/qiodevice.h>
#include <QTextStream>
#include <QPoint>

#include <utility>
#include <QVector>
#include <stdio.h>

#include <boost/shared_ptr.hpp>

#ifndef TESTS
#include "territories/territoriesConnection.h"
#endif

/**
	Klasa reprezentujaca kontynent na mapie
*/
class Continent
{
public:
	/** Konstruktor
		@param name nazwa kontynentu
		@param bonus bonus jaki otrzymujemy za zajecie calego kontytnentu
		@param territories wektor terytoriow na ktore sklada sie kontytnent
	*/
	Continent(QString name, int bonus, territoryVect territories)
		: name_(name)
		, bonus_(bonus)
		, territories_(territories){}
	/**
		@return nazwa kontytnentu
	*/
	QString getName(){ return name_; }
	/**
		@return bonus za zdobycie kontytnentu
	*/
    int bonus() const {return bonus_;}

	/**
		ustawia terytoria danego kontytentu
		@param terr wektor terytoriow
	*/
	void setTerritories(territoryVect terr) {territories_ = terr; }
	/**
		@return wektor terytoriow na ktore sklada sie kontynent
	*/
    territoryVect getTerritories() {return territories_;}
private:
	territoryVect territories_;
	const QString name_;
	const int bonus_;
};

class Territory;
class TerritoriesConnection;

/**
	Klasa reprezentujaca mape
*/
class Map {
public:
    Map() {};
	/**
		zwraca instancje mapy
	*/
    static Map& getInstance();

	/**
		laduje mape z pliku xml
		@param filename nazwa pliku z ktorego ma byc zaladowana
	*/
    bool loadMap(QString filename);

	/**
		@return wektor terytoriow na mapie
	*/
    territoryVect territories() {return territories_;}
	/**
		@return wektor kontynentow na mapie
	*/
    continentVect continents() {return continents_;}
    #ifndef TESTS
    connectionVect connections() {return connections_;}
    #endif

    pTerritory getTerritory(int id);
    territoryVect territories() const {return territories_;}
	/**
		@param id identyfiaktor zawodnika
		@return wektor terytoriow posiadanych przez danego zawodnika
	*/
    territoryVect getPlayerTerritories(PlayerId id) const;

	/**
		@return nazwa mapy
	*/
    QString mapName() const {return mapName_;}
	/**
		@param id identyfikator zawodnika
		@return id teryrtorium z pozycja startowa zawodnika
	*/
    int playerStartingPosition(PlayerId id) const;
	/**
		ustawia pozycje zawodnika na mapie
		@param id identyfikator zawodnika
		@param pos pozycja zawodnika (id terytorium)
	*/
    void setPlayerStartingPosition(PlayerId id, int pos);
	/**
		ustawia pozycje poczatkowe zawodnikow
	*/
    void setPlayerStartingPositions();
	/**
		czysci pozycje startowe zawodnikow
	*/
    void clearStartingPositions();
	/**
		losuje pozycje poczatkowe zawodnikow
	*/
    void randomizeStartingPositions();

private:
    int startingPositions[NO_PLAYERS];
    QString mapName_;
    territoryVect territories_;
    continentVect continents_;
    #ifndef TESTS
	connectionVect connections_;
    #endif
};
#endif