#include "commands/movecommand.h"

MoveCommand::MoveCommand(int fromId, int toId, UnitsId unitId, int noUnits)
        : fromId_(fromId)
        , toId_(toId)
        , unitId_(unitId)
        , noUnits_(noUnits) {
}

bool MoveCommand::registered_ = CommandsFactory::getInstance().registerFunc(CommandsId(MOVE_COMMAND),create);