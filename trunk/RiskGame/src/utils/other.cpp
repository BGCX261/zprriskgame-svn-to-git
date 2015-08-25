#include "utils/other.h"

int calculateAttack(UnitsMap& m){
    int a = 0;

    for(UnitsMap::iterator i = m.begin(); i!=m.end(); ++i){
        a += UNITS_ATTACK[i.key()] * i.value();
    }
    return a;
}

int calculateDefence(UnitsMap& m){
    int a = 0;

    for(UnitsMap::iterator i = m.begin(); i!=m.end(); ++i){
        a += UNITS_DEFENCE[i.key()] * i.value();
    }
    return a;
}

int noUnits(UnitsMap& m){
    int n=0;
    for(UnitsMap::iterator i = m.begin(); i!=m.end(); ++i){
        n += i.value();
    }
    return n;
}

void removeUnit(UnitsMap& m, int n){
    for(UnitsMap::iterator i = m.begin(); i!=m.end(); ++i){
        if(i.value() == 0)
            continue;
        if((n -= i.value())<=0){
            --i.value();
            /*if(!i.value())
                m.erase(i);*/

            return;
        }
    }
}


int combineInts(int a, int b){
    int val = 0;
    val = (a<<16) + b;
    return val;
}

int getFirstCombined(int val){
    return val >> 16;
}

int getSecondCombined(int val){
    return val&(0xF);
}
