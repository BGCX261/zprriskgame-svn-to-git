#include "calculator/interpreter.h"

Interpreter::Interpreter()
        : map_(Map::getInstance()){
}

void Interpreter::applyRaports(raportVect v){
    clear();
    separateRaports(v);
    applyObjectRaports();
    applyOwnerRaports();
    applyBattleRaports();
    calculateMoney();
}

void Interpreter::separateRaports(raportVect& v){
    for(int i=0; i<v.size(); i++){
        switch(v[i]->type()){
            case BATTLE:
                battleRaports_.push_back(dynamic_pointer_cast<BattleRaport>(v[i]));break;
            case OBJECT:
                objectRaports_.push_back(dynamic_pointer_cast<ObjectRaport>(v[i]));break;
            case OWNERSHIP:
                ownerRaports_.push_back(dynamic_pointer_cast<OwnerRaport>(v[i]));break;
            //default:
                //QFAIL("Unknown command id");
        }
    }
}

void Interpreter::clear(){
    battleRaports_.clear();
    objectRaports_.clear();
    ownerRaports_.clear();
    info_.clear();
}


void Interpreter::write(QString s){
    info_.append(s);
}

stringVect Interpreter::info(){
    return info_;
}


void Interpreter::applyObjectRaports(){
    foreach(pObRaport r, objectRaports_){
        /*pObRaport r = objectRaports_[i];*/
        pTerritory t = Map::getInstance().getTerritory(r->getTerritoryId());
        
        switch(r->getBuildId()){
            case UNIT:{
                t->setUnit(UnitsId(r->getObjectId()), r->getNoObjects());
                      }break;
            case BUILDING:{
                t->addBuilding(BuildingsId(r->getObjectId()));
                          }break;
        }
    }
}

void Interpreter::applyOwnerRaports(){
    foreach(pOwRaport r, ownerRaports_){
        Map::getInstance().getTerritory(r->getTerritoryId())->setOwnership(r->getToPlayer());
    }
}

void Interpreter::applyBattleRaports(){
    foreach(pBRaport r, battleRaports_){

        switch(r->getBattleRaportId()){
            case BORDER_BATTLE:{
                write(QString("Border battle. Armies attacking from ")
                    .append(Map::getInstance().getTerritory(getFirstCombined(r->getTerritory()))->name())
                    .append(" defeated armies attacking from ")
                    .append(Map::getInstance().getTerritory(getSecondCombined(r->getTerritory()))->name())
                    .append(" killing ")
                    .append(QString::number(r->getUnitsKill()))
                    .append(" and losing ")
                    .append(QString::number(r->getUnitsLoss())));
                               }break;
            case TERRITORY_BATTLE_CONQUERED:{
                bool hasPlayerWon;
                if(Map::getInstance().getTerritory(r->getTerritory())->ownership() 
                    == Player::getInstance().id())
                    hasPlayerWon = true;
                else
                    hasPlayerWon = false; 
                

                write(QString("Territory battle. Battle at ")
                    .append(Map::getInstance().getTerritory(r->getTerritory())->name())
                    .append(". You were ")
                    .append(hasPlayerWon?"attacking and have WON ":"defending and have LOST ")
                    .append(hasPlayerWon?"killing ":"losing ")
                    .append(QString::number(r->getUnitsKill()))
                    .append(hasPlayerWon?" and losing ":" and killing ")
                    .append(QString::number(r->getUnitsLoss())));
                                  }break;
            case TERRITORY_BATTLE_DEFENDED:{
                bool hasPlayerWon;
                if(Map::getInstance().getTerritory(r->getTerritory())->ownership() 
                    == Player::getInstance().id())
                    hasPlayerWon = true;
                else
                    hasPlayerWon = false; 
                

                write(QString("Territory battle. Battle at ")
                    .append(Map::getInstance().getTerritory(r->getTerritory())->name())
                    .append(". You were ")
                    .append(hasPlayerWon?"defending and have WON ":"attacking and have LOST ")
                    .append(hasPlayerWon?"killing ":"losing ")
                    .append(QString::number(r->getUnitsKill()))
                    .append(hasPlayerWon?" and losing ":" and killing ")
                    .append(QString::number(r->getUnitsLoss())));
                                           }break;
        }
    }
}


void Interpreter::calculateMoney(){
    int money = 0;

    foreach(pTerritory t, Map::getInstance().getPlayerTerritories(Player::getInstance().id())){
        money+=MONEY_PER_TERRITORY*(float(100+t->getEconomyBonus())/100);

    }

    foreach(pContinent c, Map::getInstance().continents()){
        bool has = true;
        foreach(pTerritory t, c->getTerritories()){
            if(t->ownership() != Player::getInstance().id()){
                has = false;
                break;
            }
        }
        
        if(has)
            money+= c->bonus() * MONEY_PER_CONTINENT_BONUS;
    }


    Player::getInstance().addMoney(money);
    write(QString("You have earned ").append(QString::number(money)));
}