#ifndef SERV_H
#define SERV_H

#include <QtCore>
#include <QtNetwork>
#include <vector>

#include <qtextstream.h>

#include <stdlib.h>

#include "utils/ids.h"
#include "utils/defs.h"
#include "utils/logger.h"
#include "raports/raport.h"
#include "raports/battleraport.h"
#include "raports/objectraport.h"
#include "raports/ownerraport.h"
#include "commands/command.h"
#include "commands/movecommand.h"
#include "commands/attackcommand.h"
#include "commands/buildcommand.h"

//class QTcpServer;

/**
	Klasa opisuj¹ca serwerow¹ stronê obs³ugi po³¹czenia sieciowego.
	--pola:
	pTcpServer - gniazdo nas³uchuj¹ce na po³¹czenia od klientów, zamykane po pierwszym po³¹czeniu;
    serverIp - jeden z adresów IP na których nas³uchuje serwer (nie loopback);
    serverPort - port na którym nas³uchuje serwer;
    pToClientSocket - gniazdo tworzone w momencie nadejœcia po³¹czenia od klienta, poprzez nie odbywa siê ca³a komunikacja z klientem;
    commands - wektor komend otrzymanych od klienta (jeszcze jako QString);
    readyCommands - wektor komend otrzymanych od klienta (ju¿ jako pCommand), gotowy do przekazania do innych modu³ów;
    serverCreated - flaga oznaczaj¹ca czy serwer pomyœlnie wystartowa³;
	--sygna³y:
	void newClientConnected() -emitowany, gdy pod³¹czy³ siê klient;
    void newVectorHasBeenReceived() - emitowany, gdy otrzymano wektor koment od klienta
    void errorClientDisconnected() - emitowany, gdy klient siê od³¹czy³
	--sloty:
    void makeConnection() - wo³ana w momencie pod³¹czenia siê nowego klienta;
    void readDataFromClient() - wo³ana gdy s¹ nowe dane przesy³ane od klienta;
    void displayError() - wo³ana gdy klient siê od³aczy³;
*/
class Server : QObject{

        Q_OBJECT
        private:
                shared_ptr<QTcpServer> pTcpServer;
                QString serverIp;
                QString serverPort;
                shared_ptr<QTcpSocket> pToClientSocket;
                std::vector<QString> commands;
                std::vector<pCommand> readyCommands;
                bool serverCreated;
        private slots:
                void makeConnection();
                void readDataFromClient();
                void displayError();
        signals:
                void newClientConnected();
                void newVectorHasBeenReceived();
                void errorClientDisconnected();
        public:
                Server();  //konstruktor
                ~Server();
				/**
					zwraca jeden z adresów IP na których nas³uchuje serwer
					@return adres IP serwera jako QString
				*/
                QString getServerIp(){return serverIp;}
				/**
					zwraca port na którym nas³uchuje serwer
					@return port serwera jako QString
				*/
                QString getServerPort(){return serverPort;}
				/**
					sprawdza czy serwer pomyœlnie wystartowa³
					@return flaga oznaczaj¹ca czy serwer wystartowa³
				*/
                bool isServerCreated(){return serverCreated;}
				/**
					zwraca wektor raportów otrzymany od serwera
					@return wektor raportów
				*/
                std::vector<pCommand> getReadyCommandsVector(){return readyCommands;}
				void createCommands();
               void sendData(QString);  //wysylanie danej do klienta
                void sendMapToClient(QString,int,int);
                void sendRaportsVectorToClient(std::vector<pRaport>);
};
#endif // SERV_H
