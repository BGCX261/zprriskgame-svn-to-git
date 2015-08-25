#include "maptest.h"


void MapTest::init(){
}  
void MapTest::cleanup(){
}
void MapTest::initTestCase(){
    map = &Map::getInstance();
    map->loadMap("testmap.xml");
}
void MapTest::cleanupTestCase(){
    map->loadMap("testmap.xml");
}

void MapTest::getTerritory(){
    pTerritory t = map->getTerritory(0);

    QVERIFY(t);

    t = map->getTerritory(10);

    QVERIFY(!t);
}

void MapTest::reload(){
    pTerritory t = map->getTerritory(0);
    int ownership = t->ownership();
    t->setOwnership(PLAYER1);

    QVERIFY(ownership!=t->ownership());

    map->loadMap("testmap.xml");
    t = map->getTerritory(0);
    QVERIFY(ownership==t->ownership());
}

void MapTest::noTerritories(){
    QCOMPARE(map->territories().size(), 4);
}
void MapTest::noContinents(){
    QCOMPARE(map->continents().size(), 2);
}
void MapTest::territoriesInContinents(){
    pTerritory t;

    t = map->getTerritory(0);
    QVERIFY(map->continents()[0]->getTerritories().contains(t));
    t = map->getTerritory(1);
    QVERIFY(map->continents()[0]->getTerritories().contains(t));

    t = map->getTerritory(2);
    QVERIFY(map->continents()[1]->getTerritories().contains(t));
    t = map->getTerritory(3);
    QVERIFY(map->continents()[1]->getTerritories().contains(t));
}
void MapTest::playerTerritories(){
    pTerritory t = map->getTerritory(0);

    QCOMPARE(map->getPlayerTerritories(NEUTRAL).size(), 4);
    QCOMPARE(map->getPlayerTerritories(PLAYER1).size(), 0);
    QCOMPARE(map->getPlayerTerritories(PLAYER2).size(), 0);

    t->setOwnership(PLAYER1);
    QCOMPARE(map->getPlayerTerritories(NEUTRAL).size(), 3);
    QCOMPARE(map->getPlayerTerritories(PLAYER1).size(), 1);
    QCOMPARE(map->getPlayerTerritories(PLAYER2).size(), 0);

    QVERIFY(map->getPlayerTerritories(PLAYER1)[0] == t);
}
void MapTest::noTerritoryBorderPoints(){
    QCOMPARE(map->getTerritory(0)->getPoints().size(),1);
    QCOMPARE(map->getTerritory(1)->getPoints().size(),2);
    QCOMPARE(map->getTerritory(2)->getPoints().size(),3);
    QCOMPARE(map->getTerritory(3)->getPoints().size(),4);
}
void MapTest::territoreNames(){
    QCOMPARE(map->getTerritory(0)->name(),QString("Id0"));
    QCOMPARE(map->getTerritory(1)->name(),QString("Id1"));
    QCOMPARE(map->getTerritory(2)->name(),QString("Id2"));
    QCOMPARE(map->getTerritory(3)->name(),QString("Id3"));
}

void MapTest::isNeighbour(){
    QVERIFY(map->getTerritory(0)->isNeighbour(1));
    QVERIFY(map->getTerritory(0)->isNeighbour(2));
    QVERIFY(map->getTerritory(0)->isNeighbour(3));

    QVERIFY(map->getTerritory(1)->isNeighbour(0));
    QVERIFY(map->getTerritory(1)->isNeighbour(2));

    QVERIFY(map->getTerritory(2)->isNeighbour(0));
    QVERIFY(map->getTerritory(2)->isNeighbour(1));

    QVERIFY(map->getTerritory(3)->isNeighbour(0));

    QVERIFY(!map->getTerritory(3)->isNeighbour(1));
    QVERIFY(!map->getTerritory(3)->isNeighbour(2));
}