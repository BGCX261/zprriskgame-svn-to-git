#ifndef COMMAND_H
#define COMMAND_H

#include <boost/shared_ptr.hpp>

#include "utils/ids.h"
#include "utils/defs.h"

/**
	Klasa komendy wysylanej do serwera przez klienta
*/
class Command
{
public:
	virtual int type() = 0;
};

#endif // COMMAND_H
