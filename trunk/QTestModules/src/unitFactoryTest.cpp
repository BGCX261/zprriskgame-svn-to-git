#include "unitfactorytest.h"


void UnitFactoryTest::init(){
}
void UnitFactoryTest::cleanup(){
}
void UnitFactoryTest::initTestCase(){
}
void UnitFactoryTest::cleanupTestCase(){
}

void UnitFactoryTest::makingPossible(){
    pUnit u = UnitsFactory::getInstance().create(INFANTRY);
    QVERIFY(u);

    u = UnitsFactory::getInstance().create(TANK);
    QVERIFY(u);
}
void UnitFactoryTest::makingImpossible(){
    pUnit u;
    for(int i=0; i<100; i++){
        int rand = qrand()%1000 + NO_UNITS;
        u = UnitsFactory::getInstance().create(UnitsId(rand));
        QVERIFY(!u);
    }
}
