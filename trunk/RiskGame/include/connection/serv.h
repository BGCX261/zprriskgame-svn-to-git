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
	Klasa opisuj�ca serwerow� stron� obs�ugi po��czenia sieciowego.
	--pola:
	pTcpServer - gniazdo nas�uchuj�ce na po��czenia od klient�w, zamykane po pierwszym po��czeniu;
    serverIp - jeden z adres�w IP na kt�rych nas�uchuje serwer (nie loopback);
    serverPort - port na kt�rym nas�uchuje serwer;
    pToClientSocket - gniazdo tworzone w momencie nadej�cia po��czenia od klienta, poprzez nie odbywa si� ca�a komunikacja z klientem;
    commands - wektor komend otrzymanych od klienta (jeszcze jako QString);
    readyCommands - wektor komend otrzymanych od klienta (ju� jako pCommand), gotowy do przekazania do innych modu��w;
    serverCreated - flaga oznaczaj�ca czy serwer pomy�lnie wystartowa�;
	--sygna�y:
	void newClientConnected() -emitowany, gdy pod��czy� si� klient;
    void newVectorHasBeenReceived() - emitowany, gdy otrzymano wektor koment od klienta
    void errorClientDisconnected() - emitowany, gdy klient si� od��czy�
	--sloty:
    void makeConnection() - wo�ana w momencie pod��czenia si� nowego klienta;
    void readDataFromClient() - wo�ana gdy s� nowe dane przesy�ane od klienta;
    void displayError() - wo�ana gdy klient si� od�aczy�;
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
					zwraca jeden z adres�w IP na kt�rych nas�uchuje serwer
					@return adres IP serwera jako QString
				*/
                QString getServerIp(){return serverIp;}
				/**
					zwraca port na kt�rym nas�uchuje serwer
					@return port serwera jako QString
				*/
                QString getServerPort(){return serverPort;}
				/**
					sprawdza czy serwer pomy�lnie wystartowa�
					@return flaga oznaczaj�ca czy serwer wystartowa�
				*/
                bool isServerCreated(){return serverCreated;}
				/**
					zwraca wektor raport�w otrzymany od serwera
					@return wektor raport�w
				*/
                std::vector<pCommand> getReadyCommandsVector(){return readyCommands;}
				void createCommands();
               void sendData(QString);  //wysylanie danej do klienta
                void sendMapToClient(QString,int,int);
                void sendRaportsVectorToClient(std::vector<pRaport>);
};
#endif // SERV_H
