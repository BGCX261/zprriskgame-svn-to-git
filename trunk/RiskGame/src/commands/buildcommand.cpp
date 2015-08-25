#include "commands/buildcommand.h"

BuildCommand::BuildCommand(int terrId, BuildId buyId, int objectId, int noObjects)
        : terrId_(terrId)
        , buyId_(buyId)
        , objectId_(objectId)
        , noObjects_(noObjects) {
}

bool BuildCommand::registered_ = CommandsFactory::getInstance().registerFunc(CommandsId(BUILD_COMMAND),create);
