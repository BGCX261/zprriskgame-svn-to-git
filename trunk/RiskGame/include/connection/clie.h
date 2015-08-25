#ifndef CLIE_H
#define CLIE_H


#include <QtCore>
#include <QtNetwork>

#include <iostream>



#include "utils/ids.h"
#include "utils/defs.h"
#include "raports/raport.h"
#include "raports/battleraport.h"
#include "raports/objectraport.h"
#include "raports/ownerraport.h"
#include "commands/command.h"
#include "commands/movecommand.h"
#include "commands/attackcommand.h"
#include "commands/buildcommand.h"
#include <vector>
#include <qtextstream.h>

#include <stdlib.h>


/**
	Klasa opisuj�ca klienck� stron� obs�ugi po��czenia sieciowego.
	--pola:
	pSocket - QTcpSocket na kt�rym b�dzie po�aczenie z serwerem;
    ipToServ - adres IP serwera z kt�rym si� ��czymy;
    portToServ - port serwera z kt�rym si� ��czymy;
    raports - wektor raport�w otrzymanych od serwera (jeszcze jako QString);
    readyRaports - wektor raport�w otrzymanych od serwera (ju� jako pRaport), gotowy do przekazania do innych modu��w;
    mapName - nazwa mapy na kt�rej odbywa si� gra, otrzymana od serwera;
    servError - napis oznaczaj�cy rodzaj b��du serwera;
    connectedToServer - flaga oznaczaj�ca czy jeste�my po��czeni z serwerem;
	--sygna�y:
	void hostDisconnected() - emitowany, gdy roz��czy si� serwer;
    void receivedRaports() - emitowany, gdy otrzymamy od serwera raporty;
	--sloty:
    void socketReadyRead() - metoda wywolywana gdy przyjd� dane od serwera;
    void displayError(QAbstractSocket::SocketError) - metoda wo�ana, gdy wyst�pi� b��d po��czenia z serwerem;
*/
class Client :QObject{
        Q_OBJECT

        private:
                shared_ptr<QTcpSocket> pSocket;
                QString ipToServ;
                QString portToServ;
                std::vector<QString> raports;
                std::vector<pRaport> readyRaports;
                QString mapName;
                QString servError;
                bool connectedToServer;
				QPair<int,int> playersPosition;

        public:
                Client(QString, QString);

                void sendToServer(QString);
                void createRaports();
				/**
					metoda sprawdzaj�ce czy pod��czyli�my si� do hosta
					@return flaga okre�laj�ca czy pod��czono si� do hosta
				*/
                bool isConnectedToServer(){return connectedToServer;}
				/**
					metoda zwracaj�ce jaki rodzaj b��du po��czenia wyst�pi�
					@return tekst z rodzajem b��du
				*/
                QString getServError(){return servError;}
				
				QPair<int,int> getPlayersPosition()
				{
					return playersPosition;
				}
				
				/**
					metoda zwracaj�ca wektor raport�w pobranych od serwera
					@return wektor raport�w std::vector<pRaport>
				*/
                std::vector<pRaport> getReadyRaportsVector(){
                    return readyRaports;
                }
                void sendCommandsToServ(std::vector<pCommand>);
				
				/**
					metoda zwracaj�ca nazw� mapy na kt�rej ma si� odbywa� gra
					@return nazwa mapy jako QString
				*/
                QString getMapName(){
					return QString("riskmap.xml");
                    //return mapName;
                }



        private slots:
                void socketReadyRead();
                void displayError(QAbstractSocket::SocketError);
       signals:
               void hostDisconnected();
               void receivedRaports();



};



#endif // CLIE_H
