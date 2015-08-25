#include "calculator/calculator.h"

Calculator::Calculator(){
}




void Calculator::commandsReceived(){
	addCommands(QVector<pCommand>::fromStdVector(Connection::getInstance().giveCommandsFromClient()));
}

void Calculator::addCommands(commandVect& v){
    for(int i=0; i<v.size(); i++){
        switch(v[i]->type()){
            case ATTACK_COMMAND:
                attackCommands_.push_back(dynamic_pointer_cast<AttackCommand>(v[i]));break;
            case BUILD_COMMAND:
                buildCommands_.push_back(dynamic_pointer_cast<BuildCommand>(v[i]));break;
            case MOVE_COMMAND:
                moveCommands_.push_back(dynamic_pointer_cast<MoveCommand>(v[i]));break;
            //default:
                //QFAIL("Unknown command id");
        }
    }

   

#if TESTS
    if(++receivedCommands_ == 1){
        receivedAllCommands();
        calculateRaports();
    }
#else
    if(++receivedCommands_ == NO_PLAYERS){
        receivedAllCommands();
        calculateRaports();
    }
#endif
}

void Calculator::calculateRaports(){
    raports_.clear();
    calculateBuilds();
    calculateMovements();
    calculateAttacks();
    calculateAssaults();

    Logger::write("Finished calculating");
    Logger::write(QString("Sending ").append(QString::number(raports_.size())).append(" raports"));
    preparedRaports(raports_);

    buildCommands_.clear();
    moveCommands_.clear();
    attackCommands_.clear();
    assaults_.clear();
    receivedCommands_ = 0;
}

raportVect Calculator::raports(){
    return raports_;
}

void Calculator::calculateBuilds(){
    for(int i=0; i<buildCommands_.size(); i++){
        pBCommand b = buildCommands_[i];
        pTerritory t = Map::getInstance().getTerritory(b->getTerrId());

        switch(b->getBuildId()){
            case UNIT:{
                t->addUnit(UnitsId(b->getObjectId()),b->getNoObjects());
                raports_.push_back(RaportFactory::getInstance().create(
                    OBJECT, UNIT, b->getTerrId(), b->getObjectId(), t->noUnits(UnitsId(b->getObjectId()))));
                      }break;
            case BUILDING:{
                t->addBuilding(BuildingsId(b->getObjectId()));
                raports_.push_back(RaportFactory::getInstance().create(
                    OBJECT, BUILDING, b->getTerrId(), b->getObjectId(),1));
                          }break;
        }
    }
}

void Calculator::calculateMovements(){
    for(int i=0; i<moveCommands_.size(); i++){
        pMCommand m = moveCommands_[i];
        pTerritory t = Map::getInstance().getTerritory(m->getToId());
        t->addUnit(m->getUnitId(),m->getNoUnits());
        raports_.push_back(RaportFactory::getInstance().create(
            OBJECT, UNIT, m->getToId(), m->getUnitId(), t->noUnits(m->getUnitId())));
    }
}



void printAttack(pAttack a){
    FileLogger::write(QString("  Attack from: ").append(QString::number(a->from()))
        .append(" to ").append(QString::number(a->to())));
    
    for(UnitsMap::iterator i=a->units().begin(); i!=a->units().end(); ++i){
        FileLogger::write(QString("    Unit ID:").append(QString::number(i.key()))
            .append(" No:").append(QString::number(i.value())));
    }

}

void printAssaults(AssaultMap& a){
    FileLogger::write("\nPrinting assaults map:\n--------------------------------");
    for(AssaultMap::iterator i=a.begin(); i!=a.end(); ++i){
        FileLogger::write(QString("Assault on: ").append(QString::number(i.key()))
        .append(" with "));
        pAttack at = i.value();
        for(UnitsMap::iterator ii=at->units().begin(); ii!=at->units().end(); ++ii){
        FileLogger::write(QString("    Unit ID:").append(QString::number(ii.key()))
            .append(" No:").append(QString::number(ii.value())));
    }

    }
}

void print(AttacksMap& a, BorderBattlesMap& b){
    FileLogger::write("\nPrinting attack map:\n--------------------------------");
    for(AttacksMap::iterator i = a.begin(); i != a.end(); i++){
        pAttack aa = i.value();
        Pair p = i.key();
        FileLogger::write(QString("From: ").append(QString::number(p.first))
            .append(" to: ").append(QString::number(p.second)));
        printAttack(aa);
    }
    FileLogger::write("\nPrinting battles map:\n--------------------------------");
    for(BorderBattlesMap::iterator i = b.begin(); i != b.end(); ++i){
        pBorderBattle aa = i.value();
        Pair p = i.key();
        FileLogger::write(QString("Between ").append(QString::number(p.first)).append(" and ").append(QString::number(p.second)));
        printAttack(aa->attack1());
        printAttack(aa->attack2());
    }

}

void Calculator::calculateAttacks(){
    AttacksMap attacks;
    BorderBattlesMap battles;

    for(int i=0; i<attackCommands_.size(); i++){
        pACommand c = attackCommands_[i];
        int from = c->getFromId();
        int to = c->getToId();
        UnitsId id = c->getUnitId();
        int no = c->getNoUnits();
        PlayerId attacker = Map::getInstance().getTerritory(from)->ownership();
        
        AttacksMap::iterator iter;

        if((iter = attacks.find(Pair(from,to))) != attacks.end()){
            iter.value()->addUnit(id, no);
            continue;
        } 
        
        if((iter = attacks.find(Pair(to,from))) != attacks.end()){
            battles.insert(Pair(to,from), pBorderBattle(
                new BorderBattle(iter.value(), pAttack(new Attack(from, to, attacker, id, no)))));
            attacks.erase(iter);
            continue;
        }

        BorderBattlesMap::iterator iter2;

        if((iter2 = battles.find(Pair(from,to))) != battles.end()){
            iter2.value()->attack1()->addUnit(id,no);
            continue;
        }

        if((iter2 = battles.find(Pair(to,from))) != battles.end()){
            iter2.value()->attack2()->addUnit(id,no);
            continue;
        }

        attacks.insert(Pair(from,to), pAttack(new Attack(from,to,attacker,id,no)));
    }

    //print(attacks, battles);

    for(BorderBattlesMap::iterator i = battles.begin(); i!=battles.end(); ++i){
        int n1 = i.value()->n(1);
        int n2 = i.value()->n(2);
        /*FileLogger::write("Battle");
        FileLogger::write(QString::number(i.value()->n(1))
            .append(" vs ").append(QString::number(i.value()->n(2))));*/
        pAttack a = i.value()->getWinner();
        /*FileLogger::write(QString::number(i.value()->n(1))
            .append(" vs ").append(QString::number(i.value()->n(2))));*/

        int terrId = combineInts(a->from(), a->to());
        int aLoss;
        int dLoss;
        if(i.value()->n(1) == 0){
            dLoss = n1;
            aLoss = n2 - i.value()->n(2);
        } else {
            dLoss = n2;
            aLoss = n1 - i.value()->n(1);
        }


        raports_.push_back(
                RaportFactory::getInstance().create(
                BATTLE, BORDER_BATTLE, terrId, aLoss, dLoss));

        attacks.insert(Pair(a->from(), a->to()), a);
    }

    battles.clear();

    //print(attacks, battles);

    for(AttacksMap::iterator i = attacks.begin(); i!=attacks.end(); ++i){
        pAttack a = i.value();
        int to = i.key().second;

        AssaultMap::iterator iter = assaults_.find(to);

        if(iter == assaults_.end()){
            assaults_.insert(to, a);
        } else {
            iter.value()->addUnits(a->units());
        }
    }

    //printAssaults(assaults_);
}

void Calculator::calculateAssaults(){
    for(AssaultMap::iterator i = assaults_.begin(); i!=assaults_.end(); ++i){
        applyAssault(i.value()->units(), i.value()->attacker(), Map::getInstance().getTerritory(i.key()));
    }
    //printAssaults(assaults_);
}

void Calculator::applyAssault(UnitsMap& attacker, PlayerId attackerId, pTerritory defenderTerritory){
    UnitsMap defender;
    PlayerId defenderId = defenderTerritory->ownership();
    int defenderDefBonus = DEFENDER_DEF_BONUS + defenderTerritory->getDefenseBonus();
    int defenderAttBonus = DEFENDER_ATT_BONUS;

    for(int i=0; i<defenderTerritory->units().size(); i++){
        pUnit u = defenderTerritory->units()[i];
        defender.insert(u->type(), u->noUnits());
    }

    int a[2];
    int d[2];
    int an = noUnits(attacker);
    int dn = noUnits(defender);
    int sum;
    int terrId = defenderTerritory->id();

    UnitsMap* m[] = {&attacker, &defender};

    while(true){
        a[0]=a[1]=d[0]=d[1]=0;

        
        a[0] = calculateAttack(*m[0]);
        d[0] = calculateDefence(*m[0]);

        a[1] = int(calculateAttack(*m[1]) * (100 + defenderAttBonus)/100);
        d[1] = int(calculateDefence(*m[1]) * (100 + defenderDefBonus)/100);


        for(int i=0; i<2; i++){
            sum = a[i] + d[(i+1)%2];
            int r = rand(sum);
                FileLogger::write(QString(i==0?"A ":"D ")
                    .append(QString::number(float(a[i])*100/sum))
                    .append("%"));
            if( r <=a[i]){  
                removeUnit(*m[(i+1)%2],rand(noUnits(*m[(i+1)%2])));
                FileLogger::write(QString("Killed. ")
                    .append(QString::number(noUnits(*m[0])))
                    .append("vs")
                    .append(QString::number(noUnits(*m[1]))));
            }
        }

        if(noUnits(attacker) == 0){
            FileLogger::write("defender won");
            for(UnitsMap::iterator i = defender.begin(); i!=defender.end(); ++i){
                raports_.push_back(
                    RaportFactory::getInstance().create(
                    OBJECT, UNIT, terrId, i.key(), i.value()));
                defenderTerritory->setUnit(i.key(), i.value());
            }
            
            raports_.push_back(
                RaportFactory::getInstance().create(
                    BATTLE, TERRITORY_BATTLE_DEFENDED, terrId, dn - noUnits(defender), an));

            
            return;
        }
        if(noUnits(defender) == 0){
            FileLogger::write("attacker won");
            for(UnitsMap::iterator i = defender.begin(); i!=defender.end(); ++i){
                raports_.push_back(
                    RaportFactory::getInstance().create(
                    OBJECT, UNIT, terrId, i.key(), i.value()));
                defenderTerritory->setUnit(i.key(), i.value());
            }
            for(UnitsMap::iterator i = attacker.begin(); i!=attacker.end(); ++i){
                raports_.push_back(
                    RaportFactory::getInstance().create(
                    OBJECT, UNIT, terrId, i.key(), i.value()));
                defenderTerritory->setUnit(i.key(), i.value());
            }
            
            raports_.push_back(
                RaportFactory::getInstance().create(
                BATTLE, TERRITORY_BATTLE_CONQUERED, terrId, an - noUnits(attacker), dn));
            raports_.push_back(
                RaportFactory::getInstance().create(
                OWNERSHIP, terrId, defenderId, attackerId, 0));

            return;
        }

    }
}

int Calculator::rand(int n) const {
    if(n==0)
        return 0;
    return qrand()%n;
}

