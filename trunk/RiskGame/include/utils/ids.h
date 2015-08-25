#ifndef IDS_H
#define IDS_H

enum PlayerId {
    PLAYER1,
    PLAYER2,
    NO_PLAYERS,
    NEUTRAL
};

enum UnitsId {
    INFANTRY,
    TANK,
    NO_UNITS
};

enum BuildingsId {
    BUNKER,
    FACTORY,
    WATCHTOWER,
    NO_BUILDINGS
};

enum CommandsId {
    ATTACK_COMMAND,
    MOVE_COMMAND,
    BUILD_COMMAND
};

enum BuildId {
    UNIT,
    BUILDING
};

enum RaportsId {
    BATTLE,
    OBJECT,
    OWNERSHIP
};

enum BattleRaportId {
    BORDER_BATTLE,
    TERRITORY_BATTLE_CONQUERED,
    TERRITORY_BATTLE_DEFENDED
};

enum NetworkMessageId {
    COMMAND_M,
    RAPORT_M,
    MAP_M,
    DONE_SENDING_M
};

enum EndGameId{
    WON,
    LOST,
    DISC
};


#endif
