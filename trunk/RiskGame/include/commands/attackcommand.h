#ifndef ATTACKCOMMAND_H
#define ATTACKCOMMAND_H

#include "commands/command.h"
#include "commands/commandsfactory.h"

/**
	Klasa reprezentujaca komende ataku
	@see Command
*/
class AttackCommand : public Command
{
public:
	/**
		Konstruktor
		@param fromId id terytorium z ktorego przeprowadzany jest atak
		@param toId id atakowanego terytorium
		@param unitId identyfikator jednostki atakujacej
		@param noUnits liczba jednostek
	*/
    AttackCommand(int fromId, int toId, UnitsId unitId, int noUnits);

    static pCommand create(int fromId, int toId, int unitId, int noUnits){
        return pCommand(new AttackCommand(fromId, toId, (UnitsId)unitId, noUnits));
    }
	virtual int type(){
		return CommandsId(ATTACK_COMMAND);
	}
	/*
		@return id terytorium z ktorego przeprowadzany jest atak
	*/
	int getFromId(){return fromId_;}
	/*
		@return id atakowanego terytorium
	*/
	int getToId(){return toId_;}
	/*
		@return identyfikator jednostki atakujacej
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

#endif // ATTACKCOMMAND_H
