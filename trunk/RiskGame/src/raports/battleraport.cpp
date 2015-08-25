#include "raports/battleraport.h"

BattleRaport::BattleRaport(BattleRaportId rapType, int ter, int unLoss, int unKill)
: territory_(ter),
    unitsLoss_(unLoss),
    unitsKill_(unKill),
        raportId_(rapType) {
}

bool BattleRaport::registered_ = RaportFactory::getInstance().registerFunc(BATTLE, create);
