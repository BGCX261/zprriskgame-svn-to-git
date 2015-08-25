#include "commands/commandsfactory.h"

CommandsFactory::CommandsFactory(){
}

bool CommandsFactory::registerFunc(CommandsId id, createCommandsFunc func){
    return callbacks_.insert(std::pair<CommandsId, createCommandsFunc>(id, func)).second;
}

pCommand CommandsFactory::create(CommandsId id, int par1, int par2, int par3, int par4){
    Callbacks::const_iterator i = callbacks_.find(id);

    if(i == callbacks_.end()){
        //jakoœ zaznaczyæ error trzeba, chocia¿ tu nigdy nie powinniœmy trafiæ - wiêc pewnie raczej assert

        return pCommand();
    } else {
        return (i->second)(par1, par2, par3, par4);
    }
}

