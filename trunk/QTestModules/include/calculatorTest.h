#ifndef CALCULATORTEST_H
#define CALCULATORTEST_H

#include <QtTest/QtTest>

#include "calculator/calculator.h"
#include "commands/commandsfactory.h"


/**
    Modu� testuj�cy dzia�anie klasy Calculator
    Poniewa� dzia�anie metod wyliczaj�cy w klasie Calculator jest uzale�nione od
    warto�ci losowych mo�liwe, �e niekt�re testy w skrajnych przypadkach 
    nie powiod� si�
    Calculator po wyliczeniu odpowiednich rozkaz�w
*/
class CalculatorTest: public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    /**
        Testuje klas� Calculator
        Sprawdza czy liczba raport�w po rozkazie ataku jest poprawna
    */
    void noRaportsAfterAttack();
    
    /**
        Testuje klas� Calculator
        Sprawdza czy liczba raport�w po rozkazie budowania jest odpowiednia
    */
    void noRaportsAfterBuild();
    
    /**
        Testuje klas� Calculator
        Sprawdza czy liczba raport�w po rozkazie prawdopodobnie wygranego ataku
        jest wi�ksza od spodziewanej
    */
    void noRaportsAfterWonAttack();
    
    /**
        Testuje klas� Calculator
        Sprawdza czy liczba raport�w po ruchu jest odpowiednia
    */
    void noRaportsAfterMove();
};


#endif