#include "connection/clie.h"


/**
	konstruktor dla klasy klienta, który próbuje siê po³¹czyæ na zadane IP i port serwera
	@param ip - adres IP serwera do którego chcemy siê po³¹czyæ
	@param port - port serwera do którego chcemy siê po³¹czyæ
*/
Client::Client(QString ip, QString port){

        ipToServ=ip;
        portToServ=port;
        servError="none";  //brak b³êdu

        pSocket = shared_ptr<QTcpSocket>(new QTcpSocket());  //socket do komunikacji
        //nasluch bledow
        connect(pSocket.get(), SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(displayError(QAbstractSocket::SocketError)));
		//po zamknieciu polaczenia zniszcz socket
        connect(pSocket.get(), SIGNAL(connectionClosed()), SLOT(deleteLater()));
		//po otrzymaniu danych wywolaj metodê przetwarzaj¹c¹ te dane
        connect(pSocket.get(), SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

		//zainicjuj ³¹czenie z serwerem na danym ip/porcie
        pSocket->connectToHost(ipToServ, portToServ.toInt());
        connectedToServer=pSocket->waitForConnected(2000); //poczekaj maksymalnie 2 sekundy na po³¹czenie
		//jeœli nie uda siê nawi¹zaæ generowany jest b³¹d QTcpSocket.error(), na który reaguje stworzona metoda displayError()


}

/**
	metoda wo³ana w razie nieudanego po³¹czenia z hostem
	@param socketError - klasa okreœlaj¹ca rodzaj b³êdu
*/
void Client::displayError(QAbstractSocket::SocketError socketError){

	
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            servError="Remote Host Closed Connection Error";  //zapisujemy rodzaj b³êdu
            //hostDisconnected();  //serwer sie odlaczyl
            break;
        case QAbstractSocket::HostNotFoundError:
            servError="Host not found.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            servError="Connection refused by the peer.";
            break;
        default:
		//sprawdzam tylko te najbardziej typowe spoœród kilkunastu rodzajów b³êdów
		//ca³a reszta dostaje komunikat "Another network error."
            servError="Another network error.";
            break;

        }
		connectedToServer=false;  //blad przy próbie pod³¹czenia do serwera, albo serwera
		hostDisconnected();  //serwer sie odlaczyl

}
/**
	metoda wysy³aj¹ca wektor komend siê do hosta
	@param cv - wektor elementów typu shared_ptr<Command>, który bêdzie przes³any przez klienta do serwera
*/
void Client::sendCommandsToServ(std::vector<pCommand> cv){
    QString s;

    for(uint i=0;i<cv.size();++i){
        sendToServer(s.setNum(NetworkMessageId(COMMAND_M))); //wysy³am typ komendy
        switch(cv.at(i)->type()){   //sprawdzam dzieki funkcji wirtualnej type() z jakim rodzajem komendy mam do czynienia
									//i odpowiednio inicjujê elementy które bêd¹ wys³ane
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

     sendToServer(s.setNum(NetworkMessageId(DONE_SENDING_M))); //wszystkie dane wys³ane
}


/**
	pomocnicza metoda s³u¿¹ca do wysy³ki jednej porcji informacji (jednego QStringa zakoñczonego znakiem nowej linii)
	@param w - ³añcuch (QString) jaki zostanie wys³any
*/
void Client::sendToServer(QString w)
    {
        // write to the server
        QTextStream os(pSocket.get());  //strumien oparty na sockecie
        os << w << "\n";


    }

/**
	metoda tworz¹ca prawdziwe raporty na podstawie wektora QString'ów, otrzymanego od serwera
*/	
void Client::createRaports(){
    //jesli sa jakies prawdziwe raporty to znaczy ze to sa stare -> trzeba je usunac
    if(!readyRaports.empty()){
        readyRaports.clear(); //shared_ptr zajmie sie usunieciem wskaznikow
    }
    pRaport ra;

    for(uint i=0;i<raports.size();){
        switch(raports.at(i).toInt()){  //sprawdz rodzaj raportu i odpowiednio stwórz prawdziwy raport
        case(RaportsId(OBJECT)):
            ra= pRaport( new ObjectRaport(BuildId(raports.at(i+1).toInt()),raports.at(i+2).toInt(),
                             raports.at(i+3).toInt(),raports.at(i+4).toInt()) );
            readyRaports.push_back(ra);
            i+=5;   //krok do pocz¹tku kolejnego raportu w wektorze QString
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
            i+=4;  //jako, ¿e ten raport jest krótszy, z³o¿ony z 3 elementów, to przesuwamy siê o mniej pozycji
            break;
        //case(RaportsId(CASH)):
        //    break;

    }
	
    //moge oczyscic wektor tymczasowych raportow
    

	}
	raports.clear();
	
}
/**
	metoda wo³ana, gdy na socket klienta przyjd¹ jakieœ dane;
	metoda "odkodowuje" wiadomoœæ i podejmuje odpowiednie kroki w zale¿noœci od rodzaju wiadomoœci
*/
void Client::socketReadyRead()
    {
    QString str;
    static int counter=0; //licznik wiadomoœci (gdyby by³y du¿e opóŸnienia na sieci i ta metoda wywo³ywa³a wiele razy, 
								//to ¿eby nie traciæ momentu w którym byliœmy z przetwarzaniem wiadomoœci)
    int messFlag; //flaga wiadomoœci
    while ( pSocket->canReadLine() ) {  //dopóki mogê czytaæ liniê
        if(counter==0){  //jeœli pierwsza czêœæ wiadomoœci
            str = pSocket->readLine();
            messFlag=str.toInt();  //flaga wiadomoœci
            if(messFlag==NetworkMessageId(DONE_SENDING_M)){//koniec przesy³u wiadomoœci
                createRaports(); //tworzê prawdziwe raporty na podstawie otrzymanych danych
                receivedRaports(); //emitujê sygna³, ¿e mam gotowe raporty
                counter=-1;  //to by³ ostatni element tej wiadomoœci, nastêpny element nale¿y do nowej wiadomoœci
            }
        }
        else{ //jeœli kolejne elementy wiadomoœci
            str = pSocket->readLine(); //czytam dalsza czêœæ wiadomoœci

            switch(messFlag){
            case NetworkMessageId(RAPORT_M): //raport
                raports.push_back(str);
                if(str.toInt()==RaportsId(OWNERSHIP)) //jeœli krótszy raport (sk³adaj¹cy siê z 3 a nie 4 elementów)
                    ++counter;							//zwiêkszam licznik, aby sie odpowiednio wczeœniej "zresetowa³"

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

