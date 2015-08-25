#ifndef UNITFACTORYTEST_H
#define UNITFACTORYTEST_H

#include <QtTest/QtTest>

#include "units/unitsfactory.h"

/**
    Modu� testuj�cy dzia�anie klasy UnitFactory
    Testy polegaj� na sprawdzeniu dzia�ania fabryki przy pr�bie tworzenia
    zar�wno zarejestrowanych jak i nie zarejestrowanych obiekt�w
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
        Funkcja testuj�ca UnitFactory.
        Sprawdza czy fabryka poprawnie generuje jednostki o znanych id
    */
    void makingPossible();

    /**
        Funkcja testuj�ca UnitFactory
        Sprawdza czy fabryka zwraca puste wska�niki przy pr�bie generowania
        jednostek o niezarejestrowanym id
    */
    void makingImpossible();
};


#endif