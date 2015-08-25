#include "units/infantry.h"

bool Infantry::registered_ = UnitsFactory::getInstance().registerFunc(UnitsId(INFANTRY),create);