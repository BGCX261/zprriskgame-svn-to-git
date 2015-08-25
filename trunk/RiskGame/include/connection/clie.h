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
	Klasa opisuj¹ca klienck¹ stronê obs³ugi po³¹czenia sieciowego.
	--pola:
	pSocket - QTcpSocket na którym bêdzie po³aczenie z serwerem;
    ipToServ - adres IP serwera z którym siê ³¹czymy;
    portToServ - port serwera z którym siê ³¹czymy;
    raports - wektor raportów otrzymanych od serwera (jeszcze jako QString);
    readyRaports - wektor raportów otrzymanych od serwera (ju¿ jako pRaport), gotowy do przekazania do innych modu³ów;
    mapName - nazwa mapy na której odbywa siê gra, otrzymana od serwera;
    servError - napis oznaczaj¹cy rodzaj b³êdu serwera;
    connectedToServer - flaga oznaczaj¹ca czy jesteœmy po³¹czeni z serwerem;
	--sygna³y:
	void hostDisconnected() - emitowany, gdy roz³¹czy siê serwer;
    void receivedRaports() - emitowany, gdy otrzymamy od serwera raporty;
	--sloty:
    void socketReadyRead() - metoda wywolywana gdy przyjd¹ dane od serwera;
    void displayError(QAbstractSocket::SocketError) - metoda wo³ana, gdy wyst¹pi³ b³¹d po³¹czenia z serwerem;
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
					metoda sprawdzaj¹ce czy pod³¹czyliœmy siê do hosta
					@return flaga okreœlaj¹ca czy pod³¹czono siê do hosta
				*/
                bool isConnectedToServer(){return connectedToServer;}
				/**
					metoda zwracaj¹ce jaki rodzaj b³êdu po³¹czenia wyst¹pi³
					@return tekst z rodzajem b³êdu
				*/
                QString getServError(){return servError;}
				
				QPair<int,int> getPlayersPosition()
				{
					return playersPosition;
				}
				
				/**
					metoda zwracaj¹ca wektor raportów pobranych od serwera
					@return wektor raportów std::vector<pRaport>
				*/
                std::vector<pRaport> getReadyRaportsVector(){
                    return readyRaports;
                }
                void sendCommandsToServ(std::vector<pCommand>);
				
				/**
					metoda zwracaj¹ca nazwê mapy na której ma siê odbywaæ gra
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
