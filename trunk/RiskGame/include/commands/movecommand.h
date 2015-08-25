#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "commands/command.h"
#include "commands/commandsfactory.h"
/**
	Klasa reprezentujaca komende przeniesienia jednostek
	@see Command
*/
class MoveCommand : public Command
{
public:
	/**
		Konstruktor
		@param fromId id terytorium z ktorego przenoszone sa jednostki
		@param toId id terytorium na ktore sa przeniesione jednostki
		@param unitId identyfikator jednostki przenoszonej
		@param noUnits liczba jednostek
	*/
    MoveCommand(int fromId, int toId, UnitsId unitId, int noUnits);

    static pCommand create(int fromId, int toId, int unitId, int noUnits){
        return pCommand(new MoveCommand(fromId, toId, (UnitsId)unitId, noUnits));
    }
	virtual int type(){
		return CommandsId(MOVE_COMMAND);
	}
	/*
		@return id terytorium z ktorego przenoszone sa jednostki
	*/
	int getFromId(){return fromId_;}
	/*
		@return id terytorium na ktore sa przeniesione jednostki
	*/
	int getToId(){return toId_;}
	/*
		@return identyfikator jednostki przenoszonej
	*/
	UnitsId getUnitId(){return unitId_;}
	/*
		@return liczba jednostek
	*/
	int getNoUnits(){return noUnits_;}

private:
    int fromId_;
    int toId_;
	static bool registered_;
    UnitsId unitId_;
    int noUnits_;
};


#endif // MOVECOMMAND_H
