#ifndef COMMANDS_FACTORY_H
#define COMMANDS_FACTORY_H

#include "commands/command.h"
#include "commands/attackcommand.h"
#include "commands/movecommand.h"
#include "commands/buildcommand.h"

#include <boost/shared_ptr.hpp>
#include <map>

/**
	Fabryka komend
	@see Command
*/
class CommandsFactory
{
public:
    typedef pCommand (*createCommandsFunc)(int par1, int par2, int par3, int par4);

    CommandsFactory();

	/**
		@return instancja fabryki komend
	*/
    static CommandsFactory& getInstance(){
        static CommandsFactory f;
        return f;
    }

    bool registerFunc(CommandsId id, createCommandsFunc func);

    pCommand create(CommandsId id, int par1, int par2, int par3, int par4);

private:
    typedef std::map<CommandsId, createCommandsFunc> Callbacks;
    Callbacks callbacks_;
};


#endif // COMMANDS_FACTORY_H
