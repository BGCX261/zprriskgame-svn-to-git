#ifndef TERRITORYTEST_H
#define TERRITORYTEST_H

#include <QtTest/QtTest>

#include "territories/territory.h"
#include "map.h"
#include "utils/defs.h"

/**
    Modu� testuj�cy dzia�anie klasy Territoyr
    Testy polegaj� na sprawdzeniu licznych metod klasy, zajmuj�cych si� m.in.
    - jednostkami
    - budynkami
    - widzalno�ci� terytorium (mg�a wojny_
    - wyliczaniem bonus�w terytorium
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
        Sprawdza czy metoda dodawania jednsotek dzia�a poprawnie
    */
    void addUnit();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda ustawiania ilo�ci jednostek dzia�a poprawnie
    */
    void setUnit();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda usuwania jednostek dzia�a poprawnie
    */
    void remUnit();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda zwracaj�ca liczb� jednostek danego typu w terytorium
        dzia�a poprawnie
    */
    void noUnitsById();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda zwracaj�ca liczb� typ�w jednostek w terytorium
        dzia�a poprawnie
    */
    void noUnitsTypes();
    
    /**
        Testuje klase Territory
        Sprawdza dzia�anie metod zwi�zanych z dodawanie oraz sprawdzaniem posiadania
        budynk�w
    */
    void buildings();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda obliczaj�ca bonus ekonomiczny dla danego terytorium dzia�a
    */
    void getEconomyBonus();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda obliczaj�ca bonus obronny dla danego terytorium dzia�a
    */
    void getDefenseBonus();
    
    /**
        Testuje klase Territory
        Sprawdza czy metoda okre�laj�ca widoczno�� danego terytorium dla gracza dzia�a
    */
    void isVisible();

private:
    pTerritory t0;
};


#endif