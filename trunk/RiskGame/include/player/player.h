#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include <QString>

#include "territories/territory.h"
#include "commands/command.h"
#include "utils/defs.h"
#include "utils/logger.h"

#include <boost/shared_ptr.hpp>

class Territory;
/**
	Klasa reprezentujaca zawodnika w grze
*/
class Player
{
public:
	/**
		Konstruktor
		@param name nazwa gracza
		@param server czy jest serverem, czy klientem
		@param money zasoby pieniezne na starcie
	*/
    Player(QString name = "Unnamed", bool server = false, int money = MONEY_STARTING);
	/**
		@return instancja gracza
	*/
    static Player& getInstance(){
        static Player instance;
        return instance;
    }

	/**
		@return zasoby pieniezne zawodnika
	*/
    int money() {return money_;}
	/**
		ustawia zasoby pieniezne zawodnika
		@param money ile pieniedzy ma miec
	*/
    void setMoney(int money) {money_ = money;}
	/**
		dodaje zasoby pieniezne dla zawodnika
		@param money ile pieniedzy dodac
	*/
    void addMoney(int money) {money_ += money;}
	/**
		@return nazwa zawodnika
	*/
    QString name() {return name_;}
	/**
		ustawia nazwe zawodnika
		@param name nazwa zawodnika
	*/
    void setName(QString name){name_ = name;}
	/**
		wskazuje ze zawodnik jest serverem lub nie
		@param isServer czy jest serverem
	*/
    void setServer(bool isServer) {isServer_ = isServer;}
	/**
		@return czy zawodnik jest serverem
	*/
	bool isServer() { return isServer_;}
	/**
		zwraca wektor akcji wykonanych przez zawodnika w turze
		@return wektor komend
	*/
    commandVect commands() {return commands_;}
	/**
		zwraca wektor akcji wykonanych przez zawodnika w turze i czysci go
		@return wektor komend
	*/
    commandVect getCommandsAndReset() {
        commandVect c = commands_;
        commands_.clear();
        return c;}
	/**
		dodaje kolejna komende do wykonania po zakonczeniu tury
		@param c komenda
	*/
    void addCommand(pCommand c);
	/**
		dodaje komendy do wykonania po zakonczeniu tury
		@param v komendy
	*/
    void addCommands(commandVect v);
	/**
		nadaje identyfikator zawodnikowi
		@param id identyfikator
	*/
    void setId(PlayerId id) {id_=id;}
	/**
		@return identyfikator zawodnika
	*/
    PlayerId id() const {return id_;}

#ifdef TESTS
    void clearCommands() {commands_.clear();}
#endif

private:
    QString name_;
    int money_;

    PlayerId id_;
    commandVect commands_;

    bool isServer_;

};

#endif // PLAYER_H
