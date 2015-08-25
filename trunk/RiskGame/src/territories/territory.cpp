#include "territories/territory.h"


Territory::Territory(pointVect points, QString name, idVect neighbours, int id)
 : points_(points)
        , id_(id)
		, neighbours_ (neighbours)
        , name_(name)
        , ownership_(NEUTRAL) {}

QPoint Territory::getCenter(){
    QPoint p(0,0);
    int size = points_.size();
    for(int i=0; i<size; i++){
        p+=points_[i];
    }
    if(size>0)
        p/=size;

    return p;
}

bool Territory::isNeighbour(int id){
    for(int i=0; i<neighbours_.size(); i++){
        if(neighbours_[i] == id)
            return true;
    }
    return false;
}

void Territory::addUnit(UnitsId id, int noUnits){
    pUnit unit = getUnit(id);

    if(unit){
        unit->addUnit(noUnits);
        return;
    }

    units_.push_back(UnitsFactory::getInstance().create(id));
    units_.back()->setNoUnits(noUnits);
}

void Territory::addBuilding(BuildingsId id){
    buildings_.push_back(BuildingsFactory::getInstance().create(id));
}

void Territory::removeUnit(UnitsId id, int noUnits){
    pUnit unit = getUnit(id);

    if(unit){
        unit->removeUnit(noUnits);
    }
}

void Territory::setUnit(UnitsId id, int noUnits){
    pUnit unit = getUnit(id);

    if(unit){
        unit->setNoUnits(noUnits);
    } else {
        addUnit(id, noUnits);
    }
}

pUnit Territory::getUnit(UnitsId id){
    for(int i=0; i<units_.size(); i++){
        pUnit u = units_[i];

        if(u->type() == id){
            return u;
        }
    }

    return pUnit();
}

int Territory::noUnits() const{
    int count = 0;

    for(int i=0; i<units_.size(); i++){
        count+=units_[i]->noUnits();
    }
    return count;
}

int Territory::noUnits(UnitsId id){
    pUnit unit = getUnit(id);

    if(unit){
        return unit->noUnits();
    }
    return 0;
}

int Territory::noUnitsTypes() const {
    int count = 0;

    for(int i=0; i<units_.size(); i++){
       if(units_[i]->noUnits() > 0)
           count++;
    }
    return count;
}

bool Territory::hasBuilding(BuildingsId id) const {
    foreach(pBuilding b, buildings_){
        if(b->type() == id)
            return true;
    }
    return false;
}

int Territory::getDefenseBonus() const{
    int bonus = 0;
    if(hasBuilding(BUNKER))
        bonus+=BUNKER_BONUS;

    return bonus;
}

int Territory::getEconomyBonus() const{
    int bonus = 0;
    if(hasBuilding(FACTORY))
        bonus+=FACTORY_BONUS;

    return bonus;
}

bool Territory::isVisible() const{
    if(ownership_ == Player::getInstance().id())
        return true;

    foreach(int id, neighbours_){
        pTerritory t = Map::getInstance().getTerritory(id);
        if(t->ownership_ == Player::getInstance().id()
            && t->hasBuilding(WATCHTOWER))
            return true;
    }
    return false;
}