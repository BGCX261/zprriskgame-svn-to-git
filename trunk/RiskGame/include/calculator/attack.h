#ifndef ATTACK_H
#define ATTACK_H

#include "utils/defs.h"

class Attack {
public:
    Attack(int from, int to, PlayerId attacker);
    Attack(int from, int to, PlayerId attacker, UnitsId id, int noUnits);

    void addUnit(UnitsId id, int noUnits);
    void addUnits(UnitsMap& map);

    int from() const;
    int to() const;
    UnitsMap& units();
    PlayerId attacker() const;
private:
    int from_;
    int to_;
    UnitsMap units_;
    PlayerId attacker_;
};

#endif