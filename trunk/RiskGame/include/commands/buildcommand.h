#ifndef BUILDCOMMAND_H
#define BUILDCOMMAND_H

#include "commands/command.h"
#include "commands/commandsfactory.h"

/**
	Klasa reprezentujaca komende budowy lub rektutacji
	@see Command
*/
class BuildCommand : public Command
{
public:
    /**
		Konstruktor
		@param terId identyfikator terytorium ktorego dotyczy komenda
		@param buyId identyfikuje czy chodzi o budynek czy jednostke	
		@param objectId identyfikator obiektu
		@param noObjetcs liczba obiektow
	*/ 
	BuildCommand(int terrId, BuildId buyId, int objectId, int noObjects);
	
    static pCommand create(int terrId, int buyId, int objectId, int noObjects){
        return pCommand(new BuildCommand(terrId, BuildId(buyId), objectId, noObjects));
    }
	virtual int type(){
		return CommandsId(BUILD_COMMAND);
	}
	/**
		@return identyfikator terytorium ktorego dotyczy komenda
	*/
	int getTerrId(){return terrId_;}
	/**
		@return czy chodzi o budynek czy jednostke
	*/
	int getBuildId(){return buyId_;}
	/**
		@return identyfikator obiektu
	*/
	int getObjectId(){return objectId_;}
	/**
		@return liczba obiektow
	*/
	int getNoObjects(){return noObjects_;}

private:
    int terrId_;
    int buyId_;
	static bool registered_;
    int objectId_;
    int noObjects_;
};

#endif // BUILDCOMMAND_H
