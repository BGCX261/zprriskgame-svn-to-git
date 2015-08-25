#ifndef RAPORT_H
#define RAPORT_H

#include "utils/ids.h"
#include "utils/defs.h"

/**
	Klasa reprezentujaca raport po zakonczonej turze i przeprowadzonych obliczeniach
	@see Calculator
*/
class Raport {
public:
    virtual int type()=0;
};

#endif
