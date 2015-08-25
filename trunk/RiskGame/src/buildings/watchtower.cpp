#include "buildings/watchtower.h"


bool Watchtower::registered_ = BuildingsFactory::getInstance().registerFunc(BuildingsId(WATCHTOWER),create);