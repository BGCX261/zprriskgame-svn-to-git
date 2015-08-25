#ifndef MAPTEST_H
#define MAPTEST_H

#include <QtTest/QtTest>
#include "map.h"

/**
    Modu³ testuj¹cy dzia³anie klasy MapTest
    Testy polegaj¹ na:
    - poprawnoœci wczytywania danych z za³¹czonego pliku mapy testmap.xml
    - sprawdzeniu poprawnoœci dzia³ania metod wyszukuj¹cych terytoria po 
    id terytorium oraz po id gracza

    Szkic przyk³adowej mapy wraz z po³aczeniami i nazwami:
    0-1
    |x
    2 3
 
    (czyli 0 ³¹czy siê z ka¿dym, a 3 tylko z 0)

    Nazwy terytoriów to "Id<nrId>"
    S¹ dwa kontynenty, pierwszy zawieraj¹cy terytoria 0 i 1, oraz drugi 
    zawieraj¹cy pozosta³e
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
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa dzia³a poprawnie po powtórnym wczytywaniu
    */
    void reload();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa poprawnie zwraca terytoria nale¿ace do mapy 
        oraz zwraca pusty wskaŸnik przy ¿¹daniu nie istniej¹cego terytorium
    */
    void getTerritory();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa poprawnie wczytuje iloœæ terytoriów
    */
    void noTerritories();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa poprawnie wczytuje iloœæ kontynentów
    */
    void noContinents();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy mapa poprawnie przydzieli³a terytoria do ich kontynentów
    */
    void territoriesInContinents();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa poprawnie zwraca terytoria posiadane przez 
        zadanego gracza
    */
    void playerTerritories();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa poprawnie wczytuje punkty okreœlaj¹ce jej granice
        na planszy
    */
    void noTerritoryBorderPoints();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa dzia³a poprawnie wczytuje nazwy terytoriów.
    */
    void territoreNames();
    
    /**
        Funkcja testuje klasê Map
        Sprawdza czy przy mapa poprawnie wczyta³a informacje o po³¹czeniach
        pomiêdzy terytoriami
    */
    void isNeighbour();

private:
    Map* map;
};


#endif