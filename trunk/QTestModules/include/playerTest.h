#ifndef PLAYERTEST_H
#define PLAYERTEST_H

#include <QtTest/QtTest>

#include "player/player.h"
#include "commands/commandsfactory.h"
#include "utils/defs.h"

/**
    Modu³ testuj¹cy dzia³anie klasy Player
    Testy polegaj¹ na sprawdzeniu poprawnoœci dzia³ania klasy przy dodawaniu
    rozkazów oraz test metod zwi¹zanych ze stanem pieniêdzy oraz id gracza
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
        Testuje klasê Player
        Sprawdza czy metoda dodaj¹ca rozkaz dzia³a
    */
    void addCommand();

    /**
        Testuje klasê Player
        Sprawdza czy metoda dodaj¹ca wektor rozkazów dzia³a
    */
    void addCommands();

    /**
        Testuje klasê Player
        Sprawdza czy metoda pobieraj¹ca i jednoczeœnie resetuj¹ca rozkazy gracza dzia³a
    */
    void sendCommand();

    /**
        Testuje klasê Player
        Sprawdza czy metody zwi¹zane z ustawianiem iloœci pieniêdzy gracza dzia³aj¹
    */
    void money();

    /**
        Testuje klasê Player
        Sprawdza czy metody zwi¹zane z ustawianiem id gracza dzia³aj¹
    */
    void id();

private:
    Player* p;
};


#endif