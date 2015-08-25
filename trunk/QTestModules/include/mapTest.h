#ifndef MAPTEST_H
#define MAPTEST_H

#include <QtTest/QtTest>
#include "map.h"

/**
    Modu� testuj�cy dzia�anie klasy MapTest
    Testy polegaj� na:
    - poprawno�ci wczytywania danych z za��czonego pliku mapy testmap.xml
    - sprawdzeniu poprawno�ci dzia�ania metod wyszukuj�cych terytoria po 
    id terytorium oraz po id gracza

    Szkic przyk�adowej mapy wraz z po�aczeniami i nazwami:
    0-1
    |x
    2 3
 
    (czyli 0 ��czy si� z ka�dym, a 3 tylko z 0)

    Nazwy terytori�w to "Id<nrId>"
    S� dwa kontynenty, pierwszy zawieraj�cy terytoria 0 i 1, oraz drugi 
    zawieraj�cy pozosta�e
*/
class MapTest: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa dzia�a poprawnie po powt�rnym wczytywaniu
    */
    void reload();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa poprawnie zwraca terytoria nale�ace do mapy 
        oraz zwraca pusty wska�nik przy ��daniu nie istniej�cego terytorium
    */
    void getTerritory();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa poprawnie wczytuje ilo�� terytori�w
    */
    void noTerritories();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa poprawnie wczytuje ilo�� kontynent�w
    */
    void noContinents();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy mapa poprawnie przydzieli�a terytoria do ich kontynent�w
    */
    void territoriesInContinents();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa poprawnie zwraca terytoria posiadane przez 
        zadanego gracza
    */
    void playerTerritories();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa poprawnie wczytuje punkty okre�laj�ce jej granice
        na planszy
    */
    void noTerritoryBorderPoints();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa dzia�a poprawnie wczytuje nazwy terytori�w.
    */
    void territoreNames();
    
    /**
        Funkcja testuje klas� Map
        Sprawdza czy przy mapa poprawnie wczyta�a informacje o po��czeniach
        pomi�dzy terytoriami
    */
    void isNeighbour();

private:
    Map* map;
};


#endif