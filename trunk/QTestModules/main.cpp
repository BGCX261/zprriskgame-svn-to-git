#include <QtTest/QtTest>
#include <iostream>

#include "unitfactorytest.h"
#include "calculatortest.h"
#include "maptest.h"
#include "playertest.h"
#include "territorytest.h"


int main(int argc, char *argv[])
{
    MapTest t1;
    QTest::qExec(&t1);

    TerritoryTest t2;
    QTest::qExec(&t2);

    PlayerTest t3;
    QTest::qExec(&t3);

    UnitFactoryTest t4;
    QTest::qExec(&t4);

    CalculatorTest t5;
    QTest::qExec(&t5);

    char a;
    std::cin >> a;
    return 0;

}
