#ifndef PLAYERTEST_H
#define PLAYERTEST_H

#include <QtTest/QtTest>

#include "player/player.h"
#include "commands/commandsfactory.h"
#include "utils/defs.h"

/**
    Modu� testuj�cy dzia�anie klasy Player
    Testy polegaj� na sprawdzeniu poprawno�ci dzia�ania klasy przy dodawaniu
    rozkaz�w oraz test metod zwi�zanych ze stanem pieni�dzy oraz id gracza
*/
class PlayerTest: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    /**
        Testuje klas� Player
        Sprawdza czy metoda dodaj�ca rozkaz dzia�a
    */
    void addCommand();

    /**
        Testuje klas� Player
        Sprawdza czy metoda dodaj�ca wektor rozkaz�w dzia�a
    */
    void addCommands();

    /**
        Testuje klas� Player
        Sprawdza czy metoda pobieraj�ca i jednocze�nie resetuj�ca rozkazy gracza dzia�a
    */
    void sendCommand();

    /**
        Testuje klas� Player
        Sprawdza czy metody zwi�zane z ustawianiem ilo�ci pieni�dzy gracza dzia�aj�
    */
    void money();

    /**
        Testuje klas� Player
        Sprawdza czy metody zwi�zane z ustawianiem id gracza dzia�aj�
    */
    void id();

private:
    Player* p;
};


#endif