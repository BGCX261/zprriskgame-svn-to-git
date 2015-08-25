#include "connection/serv.h"

#include <iostream>

/**
	konstruktor dla klasy serwera, po pomy�lnej konstrukcji mamy odpowiednio zainicjowane pola IP, port;
	inicjowana jest flaga informuj�ca o udanym lub nie rozpocz�ciu nas�uchu (serverCreated)
*/
Server::Server(){

        //tworzy serwer tcp
        pTcpServer = shared_ptr<QTcpServer>(new QTcpServer());
        //nasluch na losowym porcie na wszystkich interfejsach
     if (!pTcpServer->listen()) { //je�li nie uda�o si� rozpocz�� nas�uchu
                 serverCreated=false;
          return;
     }
     else{ //udalo sie stworzyc nasluchujacy serwer

             QString ipAddress;
              QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();  //interfejsy sieciowe komputera
                 // u�yj pierwszego nie-localhost adresu IPv4 
                 for (int i = 0; i < ipAddressesList.size(); ++i) {
                     if(ipAddressesList.at(i) != QHostAddress::LocalHost){
                        ipAddress=ipAddressesList.at(i).toString();
                        serverIp=ipAddress;
                        break;
                    }
                 }
				 //TYMCZASOWO
					serverIp = "127.0.0.1";
                 QString num;
                 num=num.setNum(pTcpServer->serverPort());
                serverPort=num;
                serverCreated=true;

				//��cze sygna� nowego po��czenia na nas�uchuj�cy socket z metod�-slotem makeConnection()
                connect(pTcpServer.get(), SIGNAL(newConnection()), this, SLOT(makeConnection()) );
         }
} //konstruktor

/**
	metoda propaguj�ca sygna� b��du od klienta
*/
void Server::displayError(){
    errorClientDisconnected();
}

/**
	metoda wo�ana po nawi�zaniu po��czenia z klientem, inicjuje socket na kt�rym b�dzie odbywa� si� komunikacja,
	zamyka nas�uchuj�cy socket, aby nikt niepowo�any si� nie do��czy� do serwera, ��czy odpowiednie sygna�y z metodami-slotami klasy
*/
void Server::makeConnection(){
		//stworzenie socketa do komunikacji z klientem
         pToClientSocket = shared_ptr<QTcpSocket>(pTcpServer->nextPendingConnection());
         //zakoncz nasluchiwanie na klientow na tym serwerze
         pTcpServer->close();
        connect(pToClientSocket.get(), SIGNAL(connectionClosed()), SLOT(deleteLater()));
        connect(pToClientSocket.get(), SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(displayError()));
        connect(pToClientSocket.get(), SIGNAL(readyRead()), SLOT(readDataFromClient()) );
        newClientConnected(); //sygna�
}

Server::~Server(){

}

/**
	pomocnicza metoda s�u��ca do wysy�ki jednej porcji informacji (jednego QStringa zako�czonego znakiem nowej linii)
	@param w - �a�cuch (QString) jaki zostanie wys�any
*/
void Server::sendData(QString w){
		//strumie� do wysy�ki na podstawie socketu
        QTextStream ts( pToClientSocket.get() );
        ts << w << "\n"; //wysy�ka danej i znaku nowej linii
}

/**
	metoda-slot, wywo�ywana, gdy klient prze�le jakie� dane; informacje te s� czytane i odpowiednio przetwarzane w zale�no�ci od ich rodzaju
*/
void Server::readDataFromClient()
 {
        QString str; //zmienna pomocnicza
        static int counter=0; //licznik wiadomo�ci (gdyby by�y du�e op�nienia na sieci i ta metoda wywo�ywa�a wiele razy, 
								//to �eby nie traci� momentu w kt�rym byli�my z przetwarzaniem wiadomo�ci)
        int messFlag;  //flaga wiadomo�ci
        while ( pToClientSocket.get()->canReadLine() ) {  //dop�ki mog� czyta� lini�
            if(counter==0){ //je�li pierwsza cz�� wiadomo�ci
                str = pToClientSocket.get()->readLine();
                messFlag=str.toInt(); //flaga wiadomo�ci

                if(messFlag==NetworkMessageId(DONE_SENDING_M)){//sko�czone przesy�anie
                    createCommands(); //pobrano wszystko i przetwarzam na komendy (tworze faktyczny wektor komend)
                    newVectorHasBeenReceived(); //wektor komend gotowy, emituj� sygna�, �e gotowy
                    counter=-1; //to by� ostatni element tej wiadomo�ci, nast�pny element nale�y do nowej wiadomo�ci
                }
            }
            else{ //je�li kolejne elementy wiadomo�ci
                str = pToClientSocket.get()->readLine();
                switch(messFlag){
                case NetworkMessageId(COMMAND_M): //komenda
                    commands.push_back(str);  //dodaje do wektora QString wszystkie komendy, dlatego, �e
											//chc� je przetworzy� dopiero po otrzymaniu kolejnych cz�ci ca�ej wiadomo�ci 
                    break;
                }
                if(counter==5){ //to by� ostatni element tej wiadomo�ci, nast�pny element nale�y do nowej wiadomo�ci
                    counter=-1;
                }
            }
            ++counter; //bezwarunkowe zwiekszenie licznika
        }
 }

/**
	metoda wysy�a map� do klienta (sam� nazw� pliku)
	@param strMap - okre�la nazw� mapy na jakiej b�dzie si� odbywa� rozgrywka
*/
void Server::sendMapToClient(QString strMap, int p1pos, int p2pos){
    QString s;
    sendData(s.setNum(NetworkMessageId(MAP_M)));
    sendData(strMap);
	sendData(s.setNum(p1pos));
	sendData(s.setNum(p2pos));
}

/**
	metoda wysy�aj�ca wektor raport�w do klienta
	@param rap - otzymany z zewn�trz wektor wiadomo�ci do wys�ania
*/
void Server::sendRaportsVectorToClient(std::vector<pRaport> rap){

    Logger::write(QString("Server: sending ").append(QString::number(rap.size()).append(" raports")));
    QString s;

    for(uint i=0;i<rap.size();++i){
        sendData(s.setNum(NetworkMessageId(RAPORT_M))); //bedzie wiadomo�� typu raport
        switch(rap.at(i)->type()){  //sprawdz jaki rodzaj raportu przetwarzamy do wysy�ki
									//i zale�nie od tego odpowiednio skomponuj elementy do wysy�ki
        case RaportsId(BATTLE):
            sendData(s.setNum(RaportsId(BATTLE))); //raport BATTLE
			//odpowiednio przerzutowujemy z typu klasy bazowej na pochodn�, bo wiemy, �e dany raport jest na pewno
			//tego typu, dzi�ki przeci��onej virtualnej metodzie type()
            sendData(s.setNum( (dynamic_cast<BattleRaport*>(rap.at(i).get()))->getBattleRaportId() ));
            sendData(s.setNum( (dynamic_cast<BattleRaport*>(rap.at(i).get()))->getTerritory() ));
            sendData(s.setNum( (dynamic_cast<BattleRaport*>(rap.at(i).get()))->getUnitsKill() ));
            sendData(s.setNum( (dynamic_cast<BattleRaport*>(rap.at(i).get()))->getUnitsLoss() ));
            break;
        case RaportsId(OBJECT):
            sendData(s.setNum(RaportsId(OBJECT)));
            sendData(s.setNum( (dynamic_cast<ObjectRaport*>(rap.at(i).get()))->getBuildId() ));
            sendData(s.setNum( (dynamic_cast<ObjectRaport*>(rap.at(i).get()))->getTerritoryId() ));
            sendData(s.setNum( (dynamic_cast<ObjectRaport*>(rap.at(i).get()))->getObjectId() ));
            sendData(s.setNum( (dynamic_cast<ObjectRaport*>(rap.at(i).get()))->getNoObjects() ));
            break;
        case RaportsId(OWNERSHIP):
            sendData(s.setNum(RaportsId(OWNERSHIP)));
            sendData(s.setNum( (dynamic_cast<OwnerRaport*>(rap.at(i).get()))->getTerritoryId() ));
            sendData(s.setNum( (dynamic_cast<OwnerRaport*>(rap.at(i).get()))->getFromPlayer() ));
             sendData(s.setNum( (dynamic_cast<OwnerRaport*>(rap.at(i).get()))->getToPlayer() ));
            break;
        //case RaportsId(CASH):
               //niezdefiniowane
        //    break;
        }
    }

     sendData(s.setNum(NetworkMessageId(DONE_SENDING_M))); //wszystkie dane wys�ane
}
/**
	metoda tworz�ca prawdziwe komendy na podstawie wektora QString'�w, otrzymanego od klienta
*/
void Server::createCommands(){
    //jesli sa jakies prawdziwe komendy to znaczy ze to sa stare -> trzeba je usunac
    if(!readyCommands.empty()){
        readyCommands.clear(); //shared_ptr zajmie sie usunieciem wskaznikow
    }
    pCommand cm;

    for(uint i=0;i<commands.size();i+=5){  //znaj�c format komendy, wiemy, �e kolejne s� co 5 element�w wektora QString'�w
        switch(commands.at(i).toInt()){  //rodzaj komendy
									//w zale�no�ci od rodzaju odpowiednio inicjujemy dan� komend�
        case(CommandsId(ATTACK_COMMAND)):
            cm= pCommand( new AttackCommand(commands.at(i+1).toInt(),commands.at(i+2).toInt(),
                             UnitsId(commands.at(i+3).toInt()),commands.at(i+4).toInt()) );
            readyCommands.push_back(cm);  //dodaj do wektora komend
            break;
        case(CommandsId(MOVE_COMMAND)):
            cm= pCommand( new MoveCommand(commands.at(i+1).toInt(),commands.at(i+2).toInt(),
                             UnitsId(commands.at(i+3).toInt()),commands.at(i+4).toInt()) );
            readyCommands.push_back(cm);
            break;
        case(CommandsId(BUILD_COMMAND)):
            cm= pCommand( new BuildCommand(commands.at(i+1).toInt(),BuildId(commands.at(i+2).toInt()),
                             commands.at(i+3).toInt(),commands.at(i+4).toInt()) );
            readyCommands.push_back(cm);
            break;
        default:
            break;
        }
    }
	//moge oczyscic wektor tymczasowych komend
    commands.clear();

}


