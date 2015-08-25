#include "connection/clie.h"


/**
	konstruktor dla klasy klienta, kt�ry pr�buje si� po��czy� na zadane IP i port serwera
	@param ip - adres IP serwera do kt�rego chcemy si� po��czy�
	@param port - port serwera do kt�rego chcemy si� po��czy�
*/
Client::Client(QString ip, QString port){

        ipToServ=ip;
        portToServ=port;
        servError="none";  //brak b��du

        pSocket = shared_ptr<QTcpSocket>(new QTcpSocket());  //socket do komunikacji
        //nasluch bledow
        connect(pSocket.get(), SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(displayError(QAbstractSocket::SocketError)));
		//po zamknieciu polaczenia zniszcz socket
        connect(pSocket.get(), SIGNAL(connectionClosed()), SLOT(deleteLater()));
		//po otrzymaniu danych wywolaj metod� przetwarzaj�c� te dane
        connect(pSocket.get(), SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

		//zainicjuj ��czenie z serwerem na danym ip/porcie
        pSocket->connectToHost(ipToServ, portToServ.toInt());
        connectedToServer=pSocket->waitForConnected(2000); //poczekaj maksymalnie 2 sekundy na po��czenie
		//je�li nie uda si� nawi�za� generowany jest b��d QTcpSocket.error(), na kt�ry reaguje stworzona metoda displayError()


}

/**
	metoda wo�ana w razie nieudanego po��czenia z hostem
	@param socketError - klasa okre�laj�ca rodzaj b��du
*/
void Client::displayError(QAbstractSocket::SocketError socketError){

	
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            servError="Remote Host Closed Connection Error";  //zapisujemy rodzaj b��du
            //hostDisconnected();  //serwer sie odlaczyl
            break;
        case QAbstractSocket::HostNotFoundError:
            servError="Host not found.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            servError="Connection refused by the peer.";
            break;
        default:
		//sprawdzam tylko te najbardziej typowe spo�r�d kilkunastu rodzaj�w b��d�w
		//ca�a reszta dostaje komunikat "Another network error."
            servError="Another network error.";
            break;

        }
		connectedToServer=false;  //blad przy pr�bie pod��czenia do serwera, albo serwera
		hostDisconnected();  //serwer sie odlaczyl

}
/**
	metoda wysy�aj�ca wektor komend si� do hosta
	@param cv - wektor element�w typu shared_ptr<Command>, kt�ry b�dzie przes�any przez klienta do serwera
*/
void Client::sendCommandsToServ(std::vector<pCommand> cv){
    QString s;

    for(uint i=0;i<cv.size();++i){
        sendToServer(s.setNum(NetworkMessageId(COMMAND_M))); //wysy�am typ komendy
        switch(cv.at(i)->type()){   //sprawdzam dzieki funkcji wirtualnej type() z jakim rodzajem komendy mam do czynienia
									//i odpowiednio inicjuj� elementy kt�re b�d� wys�ane
        case CommandsId(ATTACK_COMMAND):
            sendToServer(s.setNum(CommandsId(ATTACK_COMMAND))); //komenda ATTACK
            sendToServer(s.setNum( (dynamic_cast<AttackCommand*>(cv.at(i).get()))->getFromId() ));
            sendToServer(s.setNum( (dynamic_cast<AttackCommand*>(cv.at(i).get()))->getToId() ));
            sendToServer(s.setNum( (dynamic_cast<AttackCommand*>(cv.at(i).get()))->getUnitId() ));
            sendToServer(s.setNum( (dynamic_cast<AttackCommand*>(cv.at(i).get()))->getNoUnits() ));
            break;
        case CommandsId(MOVE_COMMAND):
            sendToServer(s.setNum(CommandsId(MOVE_COMMAND)));
            sendToServer(s.setNum( (dynamic_cast<MoveCommand*>(cv.at(i).get()))->getFromId() ));
            sendToServer(s.setNum( (dynamic_cast<MoveCommand*>(cv.at(i).get()))->getToId() ));
            sendToServer(s.setNum( (dynamic_cast<MoveCommand*>(cv.at(i).get()))->getUnitId() ));
            sendToServer(s.setNum( (dynamic_cast<MoveCommand*>(cv.at(i).get()))->getNoUnits() ));
            break;
        case CommandsId(BUILD_COMMAND):
            sendToServer(s.setNum(CommandsId(BUILD_COMMAND)));
            sendToServer(s.setNum( (dynamic_cast<BuildCommand*>(cv.at(i).get()))->getTerrId() ));
            sendToServer(s.setNum( (dynamic_cast<BuildCommand*>(cv.at(i).get()))->getBuildId() ));
             sendToServer(s.setNum( (dynamic_cast<BuildCommand*>(cv.at(i).get()))->getObjectId() ));
             sendToServer(s.setNum( (dynamic_cast<BuildCommand*>(cv.at(i).get()))->getNoObjects() ));
            break;
//        case RaportsId(CASH):
//               //niezdefiniowane
//            break;
        }
    }

     sendToServer(s.setNum(NetworkMessageId(DONE_SENDING_M))); //wszystkie dane wys�ane
}


/**
	pomocnicza metoda s�u��ca do wysy�ki jednej porcji informacji (jednego QStringa zako�czonego znakiem nowej linii)
	@param w - �a�cuch (QString) jaki zostanie wys�any
*/
void Client::sendToServer(QString w)
    {
        // write to the server
        QTextStream os(pSocket.get());  //strumien oparty na sockecie
        os << w << "\n";


    }

/**
	metoda tworz�ca prawdziwe raporty na podstawie wektora QString'�w, otrzymanego od serwera
*/	
void Client::createRaports(){
    //jesli sa jakies prawdziwe raporty to znaczy ze to sa stare -> trzeba je usunac
    if(!readyRaports.empty()){
        readyRaports.clear(); //shared_ptr zajmie sie usunieciem wskaznikow
    }
    pRaport ra;

    for(uint i=0;i<raports.size();){
        switch(raports.at(i).toInt()){  //sprawdz rodzaj raportu i odpowiednio stw�rz prawdziwy raport
        case(RaportsId(OBJECT)):
            ra= pRaport( new ObjectRaport(BuildId(raports.at(i+1).toInt()),raports.at(i+2).toInt(),
                             raports.at(i+3).toInt(),raports.at(i+4).toInt()) );
            readyRaports.push_back(ra);
            i+=5;   //krok do pocz�tku kolejnego raportu w wektorze QString
            break;
        case(RaportsId(BATTLE)):
            ra= pRaport( new BattleRaport(BattleRaportId(raports.at(i+1).toInt()),raports.at(i+2).toInt(),
                             raports.at(i+3).toInt(),raports.at(i+4).toInt()) );
            readyRaports.push_back(ra);
            i+=5;
            break;
        case(RaportsId(OWNERSHIP)):
            ra= pRaport( new OwnerRaport(raports.at(i+1).toInt(),PlayerId(raports.at(i+2).toInt()),
                           PlayerId(raports.at(i+3).toInt()) )   );
            readyRaports.push_back(ra);
            i+=4;  //jako, �e ten raport jest kr�tszy, z�o�ony z 3 element�w, to przesuwamy si� o mniej pozycji
            break;
        //case(RaportsId(CASH)):
        //    break;

    }
	
    //moge oczyscic wektor tymczasowych raportow
    

	}
	raports.clear();
	
}
/**
	metoda wo�ana, gdy na socket klienta przyjd� jakie� dane;
	metoda "odkodowuje" wiadomo�� i podejmuje odpowiednie kroki w zale�no�ci od rodzaju wiadomo�ci
*/
void Client::socketReadyRead()
    {
    QString str;
    static int counter=0; //licznik wiadomo�ci (gdyby by�y du�e op�nienia na sieci i ta metoda wywo�ywa�a wiele razy, 
								//to �eby nie traci� momentu w kt�rym byli�my z przetwarzaniem wiadomo�ci)
    int messFlag; //flaga wiadomo�ci
    while ( pSocket->canReadLine() ) {  //dop�ki mog� czyta� lini�
        if(counter==0){  //je�li pierwsza cz�� wiadomo�ci
            str = pSocket->readLine();
            messFlag=str.toInt();  //flaga wiadomo�ci
            if(messFlag==NetworkMessageId(DONE_SENDING_M)){//koniec przesy�u wiadomo�ci
                createRaports(); //tworz� prawdziwe raporty na podstawie otrzymanych danych
                receivedRaports(); //emituj� sygna�, �e mam gotowe raporty
                counter=-1;  //to by� ostatni element tej wiadomo�ci, nast�pny element nale�y do nowej wiadomo�ci
            }
        }
        else{ //je�li kolejne elementy wiadomo�ci
            str = pSocket->readLine(); //czytam dalsza cz�� wiadomo�ci

            switch(messFlag){
            case NetworkMessageId(RAPORT_M): //raport
                raports.push_back(str);
                if(str.toInt()==RaportsId(OWNERSHIP)) //je�li kr�tszy raport (sk�adaj�cy si� z 3 a nie 4 element�w)
                    ++counter;							//zwi�kszam licznik, aby sie odpowiednio wcze�niej "zresetowa�"

                break;
            case NetworkMessageId(MAP_M): //mapa
                mapName=str;
				//qDebug() << "[MAP: " << mapName <<"]";
				str = pSocket->readLine();
				if ( pSocket.get()->canReadLine() ) { 
				playersPosition.first = str.toInt();
				}
				
				if   (pSocket.get()->canReadLine() ) { 
				str = pSocket->readLine();
				playersPosition.second = str.toInt();
				}			
				
                counter=5;
                break;
            }

            if(counter==5){
                counter=-1;
            }
        }
        ++counter;
    }
}

