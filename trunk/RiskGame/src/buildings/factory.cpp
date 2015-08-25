#include "buildings/factory.h"

bool Factory::registered_ = BuildingsFactory::getInstance().registerFunc(BuildingsId(FACTORY),create);