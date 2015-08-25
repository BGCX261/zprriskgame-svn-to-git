#ifndef BORDERBATTLE_H
#define BORDERBATTLE_H

#include "utils/defs.h"
#include "utils/other.h"
#include "calculator/attack.h"


class BorderBattle {
public:
    BorderBattle(pAttack attack1, pAttack attack2);

    pAttack getWinner();

    pAttack attack1();
    pAttack attack2();

    int n(int n);
private:
    int rand(int n) const;
    pAttack attack1_;
    pAttack attack2_;
}; 


#endif