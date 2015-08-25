#ifndef CALCULATORTEST_H
#define CALCULATORTEST_H

#include <QtTest/QtTest>

#include "calculator/calculator.h"
#include "commands/commandsfactory.h"


/**
    Modu³ testuj¹cy dzia³anie klasy Calculator
    Poniewa¿ dzia³anie metod wyliczaj¹cy w klasie Calculator jest uzale¿nione od
    wartoœci losowych mo¿liwe, ¿e niektóre testy w skrajnych przypadkach 
    nie powiod¹ siê
    Calculator po wyliczeniu odpowiednich rozkazów
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
        Testuje klasê Calculator
        Sprawdza czy liczba raportów po rozkazie ataku jest poprawna
    */
    void noRaportsAfterAttack();
    
    /**
        Testuje klasê Calculator
        Sprawdza czy liczba raportów po rozkazie budowania jest odpowiednia
    */
    void noRaportsAfterBuild();
    
    /**
        Testuje klasê Calculator
        Sprawdza czy liczba raportów po rozkazie prawdopodobnie wygranego ataku
        jest wiêksza od spodziewanej
    */
    void noRaportsAfterWonAttack();
    
    /**
        Testuje klasê Calculator
        Sprawdza czy liczba raportów po ruchu jest odpowiednia
    */
    void noRaportsAfterMove();
};


#endif