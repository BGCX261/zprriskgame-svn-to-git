#ifndef UNITFACTORYTEST_H
#define UNITFACTORYTEST_H

#include <QtTest/QtTest>

#include "units/unitsfactory.h"

/**
    Modu³ testuj¹cy dzia³anie klasy UnitFactory
    Testy polegaj¹ na sprawdzeniu dzia³ania fabryki przy próbie tworzenia
    zarówno zarejestrowanych jak i nie zarejestrowanych obiektów
*/
class UnitFactoryTest: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    /**
        Funkcja testuj¹ca UnitFactory.
        Sprawdza czy fabryka poprawnie generuje jednostki o znanych id
    */
    void makingPossible();

    /**
        Funkcja testuj¹ca UnitFactory
        Sprawdza czy fabryka zwraca puste wskaŸniki przy próbie generowania
        jednostek o niezarejestrowanym id
    */
    void makingImpossible();
};


#endif