#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <boost/shared_ptr.hpp>
#include "serv.h"
#include "clie.h"
#include "utils/defs.h"
#include "utils/ids.h"

/**
	Klasa opisuj¹ca po³¹czenie sieciowe. Jest interfejsem dla zewnêtrznych klas, które nie zag³êbiaj¹c siê w implementacjê, korzystaj¹
	z udostêpnionych metod do komunikacji klient - serwer;
	--pola:
	addr - trzyma adres serwera;
	port - trzyma port serwera;
    server - faktyczna klasa serwera (jest zainicjowana wy³¹cznie w przypadku gdy zak³adamy grê);
    client - faktyczna klasa klienta (jest zainicjowana wy³¹cznie w przypadku gdy ³¹czymy siê do serwera);
	--sloty:
	//jako serwer
    void servNewCon() - wo³ana, gdy przyjdzie po³¹czenie z klientem;
    void servNewComVec() - wo³ana, gdy serwer otrzyma wektor komand od klienta;
    void servClientErr() - wo³ana gdy jest b³¹d po stronie klienta, np. roz³¹czenie;
	//jako klient
    void clientServErr() - wo³ana gdy jest b³¹d po stronie serwera, np. roz³¹czenie;
    void clientNewRapVec() - wo³ana, gdy serwer otrzyma wektor raportów od serwera;
	--sygna³y:
    //jako serwer
     void commandsVectorReady() - sygnalizuje gotowoœæ wektora komend do odczytu;
     void clientConnected() - sygnalizuje nawi¹zanie po³¹czenia z klientem;
     void clientDisconnected() - sygnalizuje roz³¹czenie siê klienta;
     //jako klient
     void serverDisconnected(); - sygnalizuje roz³¹czenie siê serwera;
     void raportsVectorReady(); - sygnalizuje gotowoœæ wektora raportów do odczytu;
*/
class Connection : public QObject
{
    Q_OBJECT
public:
	/**
		konstrukcja modu³u sieciowego z predefiniowanymi wartoœciami dla serwera
	*/
    Connection() {
		addr=QString::fromStdString("127.0.0.1");
		port=QString::fromStdString("4444");
	};

    ~Connection(){}
	/**
		statyczna metoda zwracaj¹ca instancjê obiektu modu³u sieciowego
	*/
    static Connection& getInstance(){
        static Connection instance;
        return instance;
    };

    std::vector<pCommand> giveCommandsFromClient();
	/**
		metoda powoduj¹ca wys³anie wektora raportów do klienta
		@param rap - wektor elementów klasy shared_ptr<Raport>
	*/
    void sendRaportsToClient(std::vector<pRaport> rap){
        server->sendRaportsVectorToClient(rap);
    }
    /**
		metoda wysy³aj¹ca nazwê mapy, na jakiej toczyæ siê bêdzie gra, do klienta
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
		metoda inicjuj¹ca wysy³kê komend do serwera
		@param cv - wektor typu shared_ptr<Command>
	*/
    void sendCommandsToServer(std::vector<pCommand> cv){
        client->sendCommandsToServ(cv);
    }
	/**
		metoda zwraca wektor raportów (dok³adnie to wektor shared_ptr<Raport>), które zosta³y pobrane od serwera
		@return wektor raportów
	*/
    std::vector<pRaport> giveRaportsFromServer(){
        return client->getReadyRaportsVector();
    }
    /**
		metoda zwraca rodzaj b³êdu serwera, jaki wyst¹pi³
		@return QString okreœlaj¹cy rodzaj b³êdu
	*/
    QString getClientErrorMessage(){ return client->getServError(); }
    /**
		metoda zwraca wskaŸnik (shared_ptr) do serwera
		@return modu³ serwera gry
	*/
    Server* getServer(){return server;}
	/**
		metoda zwraca wskaŸnik (shared_ptr) do klienta
		@return modu³ klienta gry
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
     void commandsVectorReady(); //i mozna pobrac ten wektor metod¹ vector<pCommand>giveCommandsFromClient()
     void clientConnected(); //do serwera podlaczyl sie klient
     void clientDisconnected(EndGameId id); //klient sie odlaczyl
     //komunikaty gdy jestes klientem:
     void serverDisconnected(EndGameId id); //serwer sie odlaczyl
     void raportsVectorReady(raportVect v); //raporty przyszly od serwera, s¹ do pobrania
                                       
};

#endif // Connection_H
