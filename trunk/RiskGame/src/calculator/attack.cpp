#include "calculator/attack.h"

Attack::Attack(int from, int to, PlayerId attacker)
: from_(from)
, to_(to)
, attacker_(attacker){
}

Attack::Attack(int from, int to, PlayerId attacker, UnitsId id, int noUnits)
: from_(from)
, to_(to)
, attacker_(attacker){
    addUnit(id, noUnits);
}

PlayerId Attack::attacker() const{
    return attacker_;
}


void Attack::addUnit(UnitsId id, int noUnits){
    UnitsMap::iterator i = units_.find(id);

    if(i == units_.end()){
        units_.insert(id, noUnits);
    } else {
        i.value() +=noUnits;
    }
}

void Attack::addUnits(UnitsMap& map){
    for(UnitsMap::iterator i=map.begin(); i!=map.end(); ++i){
        UnitsMap::iterator ii = units_.find(i.key());

        if(ii == units_.end()){
            units_.insert(i.key(), i.value());
        } else {
            ii.value()+=i.value();
        }

    }
}

int Attack::from() const{
    return from_;
}

int Attack::to() const {
    return to_;
}

UnitsMap& Attack::units(){ 
    return units_;
}
