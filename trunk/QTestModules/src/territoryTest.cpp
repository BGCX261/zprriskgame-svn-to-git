#include "territorytest.h"


void TerritoryTest::init(){
}
void TerritoryTest::cleanup(){
    t0->clearUnits();
    t0->clearBuildings();
}
void TerritoryTest::initTestCase(){
    Map& map = Map::getInstance();
    map.loadMap("testmap.xml");
    t0 = map.getTerritory(0);
}
void TerritoryTest::cleanupTestCase(){
    Player::getInstance().setId(NEUTRAL);
}


void TerritoryTest::addUnit(){
    QCOMPARE(t0->noUnits(), 0);

    t0->addUnit(INFANTRY,10);

    QCOMPARE(t0->noUnits(), 10);
    QCOMPARE(t0->noUnits(INFANTRY), 10);
    QCOMPARE(t0->noUnits(TANK), 0);

    t0->addUnit(TANK,5);

    QCOMPARE(t0->noUnits(), 15);
    QCOMPARE(t0->noUnits(INFANTRY), 10);
    QCOMPARE(t0->noUnits(TANK), 5);

}

void TerritoryTest::setUnit(){
    QCOMPARE(t0->noUnits(), 0);

    t0->setUnit(INFANTRY,10);

    QCOMPARE(t0->noUnits(), 10);
    QCOMPARE(t0->noUnits(INFANTRY), 10);
    QCOMPARE(t0->noUnits(TANK), 0);

    t0->setUnit(TANK,5);

    QCOMPARE(t0->noUnits(), 15);
    QCOMPARE(t0->noUnits(INFANTRY), 10);
    QCOMPARE(t0->noUnits(TANK), 5);

    t0->setUnit(INFANTRY,5);

    QCOMPARE(t0->noUnits(), 10);
    QCOMPARE(t0->noUnits(INFANTRY), 5);
    QCOMPARE(t0->noUnits(TANK), 5);
}

void TerritoryTest::remUnit(){
    QCOMPARE(t0->noUnits(), 0);

    t0->addUnit(INFANTRY,10);
    t0->addUnit(TANK,5);

    QCOMPARE(t0->noUnits(), 15);
    QCOMPARE(t0->noUnits(INFANTRY), 10);
    QCOMPARE(t0->noUnits(TANK), 5);


    t0->removeUnit(INFANTRY,5);

    QCOMPARE(t0->noUnits(), 10);
    QCOMPARE(t0->noUnits(INFANTRY), 5);
    QCOMPARE(t0->noUnits(TANK), 5);

}

void TerritoryTest::noUnitsById(){
    QCOMPARE(t0->noUnits(), 0);

    t0->addUnit(INFANTRY,10);
    t0->addUnit(TANK,5);

    QCOMPARE(t0->noUnits(INFANTRY),10);
    QCOMPARE(t0->noUnits(TANK),5);
}

void TerritoryTest::noUnitsTypes(){
    QCOMPARE(t0->noUnits(), 0);

    QCOMPARE(t0->noUnitsTypes(), 0);

    t0->addUnit(INFANTRY,5);
    
    QCOMPARE(t0->noUnitsTypes(), 1);

    t0->addUnit(TANK,5);

    QCOMPARE(t0->noUnitsTypes(), 2);

    t0->removeUnit(TANK,5);

    QCOMPARE(t0->noUnitsTypes(), 1);
}

void TerritoryTest::buildings(){
    QVERIFY(!(t0->hasBuilding(BUNKER)));

    t0->addBuilding(BUNKER);
    QVERIFY(t0->hasBuilding(BUNKER));


    QVERIFY(!(t0->hasBuilding(FACTORY)));

    t0->addBuilding(FACTORY);
    QVERIFY(t0->hasBuilding(FACTORY));

    QVERIFY(!(t0->hasBuilding(WATCHTOWER)));

    t0->addBuilding(WATCHTOWER);
    QVERIFY(t0->hasBuilding(WATCHTOWER));


    t0->clearBuildings();
    QVERIFY(!t0->hasBuilding(BUNKER));
    QVERIFY(!t0->hasBuilding(FACTORY));
    QVERIFY(!t0->hasBuilding(WATCHTOWER));
}

void TerritoryTest::getEconomyBonus(){
    QCOMPARE(t0->getEconomyBonus(), 0);

    t0->addBuilding(FACTORY);

    QCOMPARE(t0->getEconomyBonus(), FACTORY_BONUS);
}

void TerritoryTest::getDefenseBonus(){
    QCOMPARE(t0->getEconomyBonus(), 0);

    t0->addBuilding(BUNKER);

    QCOMPARE(t0->getDefenseBonus(), BUNKER_BONUS);
}

void TerritoryTest::isVisible(){
    QVERIFY(t0->isNeighbour(1));

    pTerritory t1 = Map::getInstance().getTerritory(1);

    t0->setOwnership(PLAYER1);
    Player::getInstance().setId(PLAYER1);
    QVERIFY(!t0->hasBuilding(WATCHTOWER));

    QVERIFY(t0->isVisible());
    QVERIFY(!t1->isVisible());

    t0->addBuilding(WATCHTOWER);
    QVERIFY(t1->isVisible());

}