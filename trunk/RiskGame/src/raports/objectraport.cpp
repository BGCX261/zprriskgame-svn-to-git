#include "raports/objectraport.h"

ObjectRaport::ObjectRaport(BuildId buildId, int ter, int objId, int noObj):
terrId_(ter),
    buildId_(buildId),
    objectId_(objId),
        noObjects_(noObj) {
}

bool ObjectRaport::registered_ = RaportFactory::getInstance().registerFunc(OBJECT, create);
