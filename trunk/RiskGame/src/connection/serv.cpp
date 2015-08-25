#include "connection/serv.h"

#include <iostream>

/**
	konstruktor dla klasy serwera, po pomyœlnej konstrukcji mamy odpowiednio zainicjowane pola IP, port;
	inicjowana jest flaga informuj¹ca o udanym lub nie rozpoczêciu nas³uchu (serverCreated)
*/
Server::Server(){

        //tworzy serwer tcp
        pTcpServer = shared_ptr<QTcpServer>(new QTcpServer());
        //nasluch na losowym porcie na wszystkich interfejsach
     if (!pTcpServer->listen()) { //jeœli nie uda³o siê rozpocz¹æ nas³uchu
                 serverCreated=false;
          return;
     }
     else{ //udalo sie stworzyc nasluchujacy serwer

             QString ipAddress;
              QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();  //interfejsy sieciowe komputera
                 // u¿yj pierwszego nie-localhost adresu IPv4 
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

				//³¹cze sygna³ nowego po³¹czenia na nas³uchuj¹cy socket z metod¹-slotem makeConnection()
                connect(pTcpServer.get(), SIGNAL(newConnection()), this, SLOT(makeConnection()) );
         }
} //konstruktor

/**
	metoda propaguj¹ca sygna³ b³êdu od klienta
*/
void Server::displayError(){
    errorClientDisconnected();
}

/**
	metoda wo³ana po nawi¹zaniu po³¹czenia z klientem, inicjuje socket na którym bêdzie odbywaæ siê komunikacja,
	zamyka nas³uchuj¹cy socket, aby nikt niepowo³any siê nie do³¹czy³ do serwera, ³¹czy odpowiednie sygna³y z metodami-slotami klasy
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
        newClientConnected(); //sygna³
}

Server::~Server(){

}

/**
	pomocnicza metoda s³u¿¹ca do wysy³ki jednej porcji informacji (jednego QStringa zakoñczonego znakiem nowej linii)
	@param w - ³añcuch (QString) jaki zostanie wys³any
*/
void Server::sendData(QString w){
		//strumieñ do wysy³ki na podstawie socketu
        QTextStream ts( pToClientSocket.get() );
        ts << w << "\n"; //wysy³ka danej i znaku nowej linii
}

/**
	metoda-slot, wywo³ywana, gdy klient przeœle jakieœ dane; informacje te s¹ czytane i odpowiednio przetwarzane w zale¿noœci od ich rodzaju
*/
void Server::readDataFromClient()
 {
        QString str; //zmienna pomocnicza
        static int counter=0; //licznik wiadomoœci (gdyby by³y du¿e opóŸnienia na sieci i ta metoda wywo³ywa³a wiele razy, 
								//to ¿eby nie traciæ momentu w którym byliœmy z przetwarzaniem wiadomoœci)
        int messFlag;  //flaga wiadomoœci
        while ( pToClientSocket.get()->canReadLine() ) {  //dopóki mogê czytaæ liniê
            if(counter==0){ //jeœli pierwsza czêœæ wiadomoœci
                str = pToClientSocket.get()->readLine();
                messFlag=str.toInt(); //flaga wiadomoœci

                if(messFlag==NetworkMessageId(DONE_SENDING_M)){//skoñczone przesy³anie
                    createCommands(); //pobrano wszystko i przetwarzam na komendy (tworze faktyczny wektor komend)
                    newVectorHasBeenReceived(); //wektor komend gotowy, emitujê sygna³, ¿e gotowy
                    counter=-1; //to by³ ostatni element tej wiadomoœci, nastêpny element nale¿y do nowej wiadomoœci
                }
            }
            else{ //jeœli kolejne elementy wiadomoœci
                str = pToClientSocket.get()->readLine();
                switch(messFlag){
                case NetworkMessageId(COMMAND_M): //komenda
                    commands.push_back(str);  //dodaje do wektora QString wszystkie komendy, dlatego, ¿e
											//chcê je przetworzyæ dopiero po otrzymaniu kolejnych czêœci ca³ej wiadomoœci 
                    break;
                }
                if(counter==5){ //to by³ ostatni element tej wiadomoœci, nastêpny element nale¿y do nowej wiadomoœci
                    counter=-1;
                }
            }
            ++counter; //bezwarunkowe zwiekszenie licznika
        }
 }

/**
	metoda wysy³a mapê do klienta (sam¹ nazwê pliku)
	@param strMap - okreœla nazwê mapy na jakiej bêdzie siê odbywaæ rozgrywka
*/
void Server::sendMapToClient(QString strMap, int p1pos, int p2pos){
    QString s;
    sendData(s.setNum(NetworkMessageId(MAP_M)));
    sendData(strMap);
	sendData(s.setNum(p1pos));
	sendData(s.setNum(p2pos));
}

/**
	metoda wysy³aj¹ca wektor raportów do klienta
	@param rap - otzymany z zewn¹trz wektor wiadomoœci do wys³ania
*/
void Server::sendRaportsVectorToClient(std::vector<pRaport> rap){

    Logger::write(QString("Server: sending ").append(QString::number(rap.size()).append(" raports")));
    QString s;

    for(uint i=0;i<rap.size();++i){
        sendData(s.setNum(NetworkMessageId(RAPORT_M))); //bedzie wiadomoœæ typu raport
        switch(rap.at(i)->type()){  //sprawdz jaki rodzaj raportu przetwarzamy do wysy³ki
									//i zale¿nie od tego odpowiednio skomponuj elementy do wysy³ki
        case RaportsId(BATTLE):
            sendData(s.setNum(RaportsId(BATTLE))); //raport BATTLE
			//odpowiednio przerzutowujemy z typu klasy bazowej na pochodn¹, bo wiemy, ¿e dany raport jest na pewno
			//tego typu, dziêki przeci¹¿onej virtualnej metodzie type()
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

     sendData(s.setNum(NetworkMessageId(DONE_SENDING_M))); //wszystkie dane wys³ane
}
/**
	metoda tworz¹ca prawdziwe komendy na podstawie wektora QString'ów, otrzymanego od klienta
*/
void Server::createCommands(){
    //jesli sa jakies prawdziwe komendy to znaczy ze to sa stare -> trzeba je usunac
    if(!readyCommands.empty()){
        readyCommands.clear(); //shared_ptr zajmie sie usunieciem wskaznikow
    }
    pCommand cm;

    for(uint i=0;i<commands.size();i+=5){  //znaj¹c format komendy, wiemy, ¿e kolejne s¹ co 5 elementów wektora QString'ów
        switch(commands.at(i).toInt()){  //rodzaj komendy
									//w zale¿noœci od rodzaju odpowiednio inicjujemy dan¹ komendê
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


