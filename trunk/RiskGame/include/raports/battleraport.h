#ifndef BATTLERAPORT_H
#define BATTLERAPORT_H

#include "raports/raport.h"
#include "raports/raportfactory.h"


/**
	Klasa reprezentujaca raport z przeprowadzonych bitew
	@see Raport
	@see Calculator
*/
class BattleRaport : public Raport{	
public:
	/**
		Kontruktor
		@param rapType rodzaj raportu
		@param ter identyfikator terytorium ktorego dotyczy raport
		@param unLoss liczba straconych jednostek
		@param unKill liczba jednostek zabitych
	*/
    BattleRaport(BattleRaportId rapType, int ter, int unLoss, int unKill);

    static pRaport create(int rapType, int ter, int unLoss, int unKill){
        return pRaport(new BattleRaport(BattleRaportId(rapType), ter, unLoss, unKill));
    }

    virtual int type(){
		return RaportsId(BATTLE);
	}
	/**
		@return typ raportu bitewnego
	*/
    BattleRaportId getBattleRaportId(){
        return raportId_;
    }
	/**
		@return gdzie odbyla sie bitwa
	*/
    int getTerritory(){
        return territory_;
    }
	/**
		@return stracone jednostki
	*/
    int getUnitsLoss(){
        return unitsLoss_;
    }
	/**
		@return zabite jednostki przeciwnika
	*/
    int getUnitsKill(){
        return unitsKill_;
    }

private:
    int territory_; //gdzie by³a bitwa
    int unitsLoss_; //ile straci³ zwyciêzca
    int unitsKill_; //ile zabito. Czyli ile straci³ pokonany
    BattleRaportId raportId_; //typ raportu

    static bool registered_;
};

#endif
