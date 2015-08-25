#include "raports/ownerraport.h"

OwnerRaport::OwnerRaport(int terrId, PlayerId from, PlayerId to):
terrId_(terrId),
    fromPlayer_(from),
        toPlayer_(to) {
}

bool OwnerRaport::registered_ = RaportFactory::getInstance().registerFunc(OWNERSHIP, create);
