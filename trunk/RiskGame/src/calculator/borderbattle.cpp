#include "calculator/borderbattle.h"

BorderBattle::BorderBattle(pAttack attack1, pAttack attack2)
        : attack1_(attack1)
        , attack2_(attack2){}


pAttack BorderBattle::getWinner(){
    int a[2];
    int d[2];
    int sum;
    UnitsMap* m[] = {&attack1_->units(), &attack2_->units()};
    pAttack at[2] = {attack1_, attack2_};

    while(true){
        a[0]=a[1]=d[0]=d[1]=0;

        for(int i=0; i<2; i++){
            a[i] = calculateAttack(*m[i]);
            d[i] = calculateDefence(*m[i]);
        }

        for(int i=0; i<2; i++){
            sum = a[i] + d[(i+1)%2];
            if(rand(sum) <=a[1]){
                removeUnit(*m[i],rand(noUnits(*m[i])));
                if(noUnits(*m[i]) == 0)
                    return at[(i+1)%2];
            }
        }
    }
    return pAttack();
}

pAttack BorderBattle::attack1(){
    return attack1_;
}

pAttack BorderBattle::attack2(){
    return attack2_;
}

int BorderBattle::rand(int n)const{
    return qrand()%n;
}

int BorderBattle::n(int n){
    if(n==1){
        return noUnits(attack1_->units());
    }
    if(n==2){
        return noUnits(attack2_->units());
    }

    return -1;
}