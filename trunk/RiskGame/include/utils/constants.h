#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

#ifndef TESTS
#include <QColor>
#endif

static const QString UNITS_NAME[] = {
    "Infantry",
    "Tank"
};

static const int UNITS_ATTACK[] = {
    5,
    15
};

static const int UNITS_DEFENCE[] = {
    10,
    15
};

static const int UNITS_COST[] = {
    30,
    100
};

static const QString BUILDINGS_NAME[] = {
    "bunker",
    "factory",
    "watchtower"
};

static const int BUILDINGS_COST[] = {
    500,
    1000,
    200
};

#ifndef TESTS
static const QColor PLAYER_COLORS[] = {
    Qt::green,
    Qt::red,
    Qt::gray,
    Qt::gray
};
#endif

static int BUNKER_BONUS = 100;
static int FACTORY_BONUS = 30;
static int DEFENDER_DEF_BONUS = 50;
static int DEFENDER_ATT_BONUS = 50;

static const int PEN_WIDTH_NORMAL = 1;
static const int PEN_WIDTH_SELECTED = 3;

static const int BRUSH_LIGHT_NORMAL = 100;
static const int BRUSH_LIGHT_MIN = 80;
static const int BRUSH_LIGHT_MAX = 120;

static const int STARTING_INFANTRY_NEUTRAL = 5;
static const int STARTING_INFANTRY_PLAYER = 20;

static const int MONEY_STARTING = 1000;
static const int MONEY_PER_TERRITORY = 100;
static const int MONEY_PER_CONTINENT_BONUS = 200;
static const int MONEY_MIN_PER_TURN = 200;

#endif