#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <boost/shared_ptr.hpp>
#include "serv.h"
#include "clie.h"
#include "utils/defs.h"
#include "utils/ids.h"

/**
	Klasa opisuj�ca po��czenie sieciowe. Jest interfejsem dla zewn�trznych klas, kt�re nie zag��biaj�c si� w implementacj�, korzystaj�
	z udost�pnionych metod do komunikacji klient - serwer;
	--pola:
	addr - trzyma adres serwera;
	port - trzyma port serwera;
    server - faktyczna klasa serwera (jest zainicjowana wy��cznie w przypadku gdy zak�adamy gr�);
    client - faktyczna klasa klienta (jest zainicjowana wy��cznie w przypadku gdy ��czymy si� do serwera);
	--sloty:
	//jako serwer
    void servNewCon() - wo�ana, gdy przyjdzie po��czenie z klientem;
    void servNewComVec() - wo�ana, gdy serwer otrzyma wektor komand od klienta;
    void servClientErr() - wo�ana gdy jest b��d po stronie klienta, np. roz��czenie;
	//jako klient
    void clientServErr() - wo�ana gdy jest b��d po stronie serwera, np. roz��czenie;
    void clientNewRapVec() - wo�ana, gdy serwer otrzyma wektor raport�w od serwera;
	--sygna�y:
    //jako serwer
     void commandsVectorReady() - sygnalizuje gotowo�� wektora komend do odczytu;
     void clientConnected() - sygnalizuje nawi�zanie po��czenia z klientem;
     void clientDisconnected() - sygnalizuje roz��czenie si� klienta;
     //jako klient
     void serverDisconnected(); - sygnalizuje roz��czenie si� serwera;
     void raportsVectorReady(); - sygnalizuje gotowo�� wektora raport�w do odczytu;
*/
class Connection : public QObject
{
    Q_OBJECT
public:
	/**
		konstrukcja modu�u sieciowego z predefiniowanymi warto�ciami dla serwera
	*/
    Connection() {
		addr=QString::fromStdString("127.0.0.1");
		port=QString::fromStdString("4444");
	};

    ~Connection(){}
	/**
		statyczna metoda zwracaj�ca instancj� obiektu modu�u sieciowego
	*/
    static Connection& getInstance(){
        static Connection instance;
        return instance;
    };

    std::vector<pCommand> giveCommandsFromClient();
	/**
		metoda powoduj�ca wys�anie wektora raport�w do klienta
		@param rap - wektor element�w klasy shared_ptr<Raport>
	*/
    void sendRaportsToClient(std::vector<pRaport> rap){
        server->sendRaportsVectorToClient(rap);
    }
    /**
		metoda wysy�aj�ca nazw� mapy, na jakiej toczy� si� b�dzie gra, do klienta
		@param mapName - nazwa mapy
	*/
    void sendMap(QString mapName, int p1pos, int p2pos){
        server->sendMapToClient(mapName, p1pos, p2pos);
    }
    bool createServer();
    QString getAddress();
    QString getPort();

	QString getMapName()
	{
		return client->getMapName();
	}

	QPair<int,int> getPlayersPosition()
	{
		return client->getPlayersPosition();
	}
    //metody dla klienta
    bool conn(QString address, QString port);
	/**
		metoda inicjuj�ca wysy�k� komend do serwera
		@param cv - wektor typu shared_ptr<Command>
	*/
    void sendCommandsToServer(std::vector<pCommand> cv){
        client->sendCommandsToServ(cv);
    }
	/**
		metoda zwraca wektor raport�w (dok�adnie to wektor shared_ptr<Raport>), kt�re zosta�y pobrane od serwera
		@return wektor raport�w
	*/
    std::vector<pRaport> giveRaportsFromServer(){
        return client->getReadyRaportsVector();
    }
    /**
		metoda zwraca rodzaj b��du serwera, jaki wyst�pi�
		@return QString okre�laj�cy rodzaj b��du
	*/
    QString getClientErrorMessage(){ return client->getServError(); }
    /**
		metoda zwraca wska�nik (shared_ptr) do serwera
		@return modu� serwera gry
	*/
    Server* getServer(){return server;}
	/**
		metoda zwraca wska�nik (shared_ptr) do klienta
		@return modu� klienta gry
	*/
    Client* getClient(){return client;}
private:
	QString addr;
	QString port;
    Server* server;
    Client* client;
private slots:
    void servNewCon();
    void servNewComVec();
    void servClientErr();
    void clientServErr();
    void clientNewRapVec();
signals:
    //komunikaty gdy jestes serwerem:
     void commandsVectorReady(); //i mozna pobrac ten wektor metod� vector<pCommand>giveCommandsFromClient()
     void clientConnected(); //do serwera podlaczyl sie klient
     void clientDisconnected(EndGameId id); //klient sie odlaczyl
     //komunikaty gdy jestes klientem:
     void serverDisconnected(EndGameId id); //serwer sie odlaczyl
     void raportsVectorReady(raportVect v); //raporty przyszly od serwera, s� do pobrania
                                       
};

#endif // Connection_H
