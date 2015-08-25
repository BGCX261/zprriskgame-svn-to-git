#include "territories/territoryinfodisplay.h"
#include "map.h"

void TerritoryInfoDisplay::showTerritoryInfo(int id){
    pTerritory t = Map::getInstance().getTerritory(id);

    QString s("Territory info ");
    s.append(t->name());
    s.append("\n");

    if(t->isVisible()){
        bool hasAny = false;
        s.append("Units:\n");
        for(int i=0; i<t->units().size(); i++){
            pUnit u = t->units()[i];
            if(u->noUnits()<=0)
                continue;

            hasAny = true;
            QString us = u->name();
            us.append(": ").append(QString::number(u->noUnits()));
            s.append(us).append("\n");
        }
        if(!hasAny)
            s.append("None");

        hasAny = false;
        s.append("\nBuildings:\n");
        for(int i=0; i<NO_BUILDINGS; i++){
            if(t->hasBuilding(BuildingsId(i))){
                s.append(BUILDINGS_NAME[i]).append("\n");
                hasAny = true;
            }

        }
        if(!hasAny)
            s.append("None");

    } else {
        s.append("Territory not visible");
    }

    setText(s);
}

void TerritoryInfoDisplay::hideTerritoryInfo(){
    setText("");
}
