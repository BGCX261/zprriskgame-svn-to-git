#include "commands/attackcommand.h"

AttackCommand::AttackCommand(int fromId, int toId, UnitsId unitId, int noUnits)
        : fromId_(fromId)
        , toId_(toId)
        , unitId_(unitId)
        , noUnits_(noUnits) {
}

bool AttackCommand::registered_ = CommandsFactory::getInstance().registerFunc(ATTACK_COMMAND, create);
