#include "calculatortest.h"

void CalculatorTest::init(){
}
void CalculatorTest::cleanup(){
}
void CalculatorTest::initTestCase(){
}
void CalculatorTest::cleanupTestCase(){
}

void CalculatorTest::noRaportsAfterAttack(){
    commandVect v;
    int recvRaports;

    Map::getInstance().getTerritory(1)->setUnit(INFANTRY,100);
    v.push_back(pCommand(CommandsFactory::getInstance().create(
        ATTACK_COMMAND, 0,1,INFANTRY,1)));
    Calculator::getInstance().addCommands(v);

    raportVect r = Calculator::getInstance().raports();
    recvRaports = r.size();

    QCOMPARE(recvRaports,2);
    Map::getInstance().getTerritory(1)->setUnit(INFANTRY,0);
}

void CalculatorTest::noRaportsAfterBuild(){
    commandVect v;
    int recvRaports;

    v.push_back(pCommand(CommandsFactory::getInstance().create(
        BUILD_COMMAND, 0,UNIT,INFANTRY,10)));

    Calculator::getInstance().addCommands(v);
    recvRaports = Calculator::getInstance().raports().size();

    QCOMPARE(recvRaports, 1);
}

void CalculatorTest::noRaportsAfterWonAttack(){
    commandVect v;
    int recvRaports;

    Map::getInstance().getTerritory(1)->setUnit(INFANTRY,1);
    v.push_back(pCommand(CommandsFactory::getInstance().create(
        ATTACK_COMMAND, 0,1,INFANTRY,100)));
    Calculator::getInstance().addCommands(v);

    raportVect r = Calculator::getInstance().raports();
    recvRaports = r.size();

    QCOMPARE(recvRaports,4);
    Map::getInstance().getTerritory(1)->setUnit(INFANTRY,0);
}

void CalculatorTest::noRaportsAfterMove(){
    commandVect v;
    int recvRaports;

    v.push_back(pCommand(CommandsFactory::getInstance().create(
        MOVE_COMMAND, 0,1,INFANTRY,10)));

    Calculator::getInstance().addCommands(v);
    recvRaports = Calculator::getInstance().raports().size();

    QCOMPARE(recvRaports, 1);
}

