#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "utils/defs.h"
#include "utils/ids.h"
#include "map.h"

#include "utils/filelogger.h"

#include "commands/command.h"
#include "commands/attackcommand.h"
#include "commands/movecommand.h"
#include "commands/buildcommand.h"

#include "raports/raport.h"
#include "raports/battleraport.h"
#include "raports/objectraport.h"
#include "raports/ownerraport.h"
#include "raports/raportfactory.h"

#include "calculator/borderbattle.h"
#include "calculator/attack.h"

#include "connection/connection.h"


#include <QObject>
#include <QPair>
#include <QMap>

#include <boost/shared_ptr.hpp>

using namespace boost;

/**
	Klasa reprezentujaca kalkulator obliczajacy przebieg rozgrywki zgodnie z otrzymanymi komendami i generujacy raporty
	@see Raport
	@see Command
*/
class Calculator : public QObject
{
    Q_OBJECT
public:
    Calculator();

    typedef shared_ptr<BuildCommand> pBCommand;
    typedef shared_ptr<AttackCommand> pACommand;
    typedef shared_ptr<MoveCommand> pMCommand;

    typedef QVector<pBCommand> bVect;
    typedef QVector<pACommand> aVect;
    typedef QVector<pMCommand> mVect;

	/**
		@return	instancja kalkulatora
	*/
    static Calculator& getInstance(){
        static Calculator instance;
        return instance;
    }

	/**
		dodaje wektor komend od servera lub klienta
		@param v wektor komend
	*/
    void addCommands(commandVect& v);
	/**
		@return vektor raportow po obliczeniu rozgrywki
	*/
    raportVect raports();
signals:
    void preparedRaports(raportVect v);
    void receivedAllCommands();
public slots:
	void commandsReceived();

private:
    void calculateRaports();

    void calculateBuilds();
    void calculateMovements();
    void calculateAttacks();
    void calculateAssaults();

    void applyAssault(UnitsMap& attacker, PlayerId attackerId, pTerritory defenderTerritory);

    int rand(int n) const ;


    int receivedCommands_;
    bVect buildCommands_;
    mVect moveCommands_;
    aVect attackCommands_;
    raportVect raports_;
    AssaultMap assaults_;


};

#endif // CALCULATOR_H
