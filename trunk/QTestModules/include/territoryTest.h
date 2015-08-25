#ifndef TERRITORYTEST_H
#define TERRITORYTEST_H

#include <QtTest/QtTest>

#include "territories/territory.h"
#include "map.h"
#include "utils/defs.h"

/**
    Modu³ testuj¹cy dzia³anie klasy Territoyr
    Testy polegaj¹ na sprawdzeniu licznych metod klasy, zajmuj¹cych siê m.in.
    - jednostkami
    - budynkami
    - widzalnoœci¹ terytorium (mg³a wojny_
    - wyliczaniem bonusów terytorium
*/
class TerritoryTest: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    /**
        Testuje klase Territory
        Sprawdza czy metoda dodawania jednsotek dzia³a poprawnie
    */
    void addUnit();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda ustawiania iloœci jednostek dzia³a poprawnie
    */
    void setUnit();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda usuwania jednostek dzia³a poprawnie
    */
    void remUnit();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda zwracaj¹ca liczbê jednostek danego typu w terytorium
        dzia³a poprawnie
    */
    void noUnitsById();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda zwracaj¹ca liczbê typów jednostek w terytorium
        dzia³a poprawnie
    */
    void noUnitsTypes();
    
    /**
        Testuje klase Territory
        Sprawdza dzia³anie metod zwi¹zanych z dodawanie oraz sprawdzaniem posiadania
        budynków
    */
    void buildings();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda obliczaj¹ca bonus ekonomiczny dla danego terytorium dzia³a
    */
    void getEconomyBonus();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda obliczaj¹ca bonus obronny dla danego terytorium dzia³a
    */
    void getDefenseBonus();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda okreœlaj¹ca widocznoœæ danego terytorium dla gracza dzia³a
    */
    void isVisible();

private:
    pTerritory t0;
};


#endif