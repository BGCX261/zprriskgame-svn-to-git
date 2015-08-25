#ifndef DEFS_H
#define DEFS_H

#include <boost/shared_ptr.hpp>
#include "utils/ids.h"
#include <QVector>
#include <QPoint>
#include <QPair>
#include <QMap>

using namespace boost;

class Territory;
class Continent;

class Command;
class Building;
class Unit;
class Raport;


class BorderBattle;
class Attack;

typedef shared_ptr<Territory> pTerritory;
typedef shared_ptr<Continent> pContinent;

typedef shared_ptr<Command> pCommand;
typedef shared_ptr<Building> pBuilding;
typedef shared_ptr<Unit> pUnit;
typedef shared_ptr<Raport> pRaport;

typedef QVector<pTerritory> territoryVect;
typedef QVector<pContinent> continentVect;  
typedef QVector<pCommand> commandVect;
typedef QVector<pBuilding> buildingVect;
typedef QVector<pUnit> unitVect;
typedef QVector<pRaport> raportVect;

typedef QVector<QPoint> pointVect;
typedef QVector<int> idVect;
typedef QVector<QString> stringVect;

typedef shared_ptr<BorderBattle> pBorderBattle;
typedef shared_ptr<Attack> pAttack;
typedef QPair<int, int> Pair;
typedef QMap<Pair, pBorderBattle> BorderBattlesMap;
typedef QMap<Pair, pAttack> AttacksMap;
typedef QMap<int, pAttack> AssaultMap;
typedef QMap<UnitsId, int> UnitsMap;
typedef QPair<int, UnitsMap> BattleWinnerInfo;

#ifndef TESTS
class TerritoriesConnection;
typedef shared_ptr<TerritoriesConnection> pConnection;
typedef QVector<pConnection> connectionVect;
#endif

#endif
