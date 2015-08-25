#include "units/tank.h"

bool Tank::registered_ = UnitsFactory::getInstance().registerFunc(UnitsId(TANK),create);