#include "buildings/bunker.h"

bool Bunker::registered_ = BuildingsFactory::getInstance().registerFunc(BuildingsId(BUNKER),create);