
#include "connection/connection.h"

/**
	metoda tworzy nowy serwer, jeœli operacja siê powiedzie zwraca true, w przeciwnym razie false
	@return flaga oznaczaj¹ca czy serwer wystartowa³
*/
bool Connection::createServer(){
	//tworze 
        server=new Server();

        //connect wy³¹cznie jeœli uda³o mi siê stworzyæ serwer
        if(server->isServerCreated()){
            connect(reinterpret_cast<QObject*>(server), SIGNAL(newClientConnected()),
                    this, SLOT(servNewCon()));
        }
    return server->isServerCreated();

}
/**
	metoda tworzy klienta, który ³¹czy siê w momencie tworzenia z podanym serwerem, 
	jeœli operacja siê powiedzie zwraca true, w przeciwnym razie false
	@param address - okreœla adres IP z jakim klient spróbuje siê po³¹czyæ
	@param port - okreœla port z jakim klient spróbuje siê po³¹czyæ
	@return flaga oznaczaj¹ca czy uda³o siê po³¹czyæ z hostem
*/
bool Connection::conn(QString address, QString port){
	//tworze, wewn¹trz konstruktora jest te¿ próba ³¹czenia
        client = new Client(address,port);
		//sygna³y jeœli siê po³¹czy³em
        if(client->isConnectedToServer()){
            connect(reinterpret_cast<QObject*>(client), SIGNAL(hostDisconnected()), this, SLOT(clientServErr()));
            connect(reinterpret_cast<QObject*>(client), SIGNAL(receivedRaports()), this, SLOT(clientNewRapVec()));
        }
        return client->isConnectedToServer();
}
/**
	metoda zwraca pierwszy z listy interfejsów sieciowych komputera, nasluchujacy adres ip i nie jest to interfejs loopback; 
	@return adres IPv4 na jakim nas³uchuje serwer (jako QString)
*/
QString Connection::getAddress(){
    //zwraca pierwszy nasluchujacy ip i nie loopback
    return server->getServerIp();
}
/**
	metoda zwraca wylosowany port na którym s³ucha serwer 
	@return port na jakim serwer nas³uchuje
*/
QString Connection::getPort(){
    return server->getServerPort();
}

/**
	metoda zwraca wektor komand (dok³adnie to wektor shared_ptr<Command>), które zosta³y pobrane od klienta
	@return wektor komend (std::vector<pCommand>)
*/
std::vector<pCommand> Connection::giveCommandsFromClient(){

    return server->getReadyCommandsVector();
}

//////sloty
/**
	metoda-slot, wo³ana, gdy pod³¹cza siê nowy klient (powoduje pod³¹czenie odpowiednich sygna³ów do slotów i emisjê clientConnected())
*/
void Connection::servNewCon(){
    connect(reinterpret_cast<QObject*>(server), SIGNAL(newVectorHasBeenReceived()),
            this, SLOT(servNewComVec()));
    connect(reinterpret_cast<QObject*>(server), SIGNAL(errorClientDisconnected()),
            this, SLOT(servClientErr()));
    clientConnected(); //sygnal
}

/**
	propagacja sygna³u otrzymania wektora komend od klienta; metoda sygnalizuje gdy wektor jest gotowy poprzez sygna³
*/
void Connection::servNewComVec(){
    commandsVectorReady(); //sygnal
}
/**
	propagacja sygna³u b³êdu klienta; metoda sygnalizuje poprzez emisjê sygna³u
*/
void Connection::servClientErr(){
    clientDisconnected(DISC); //sygnal
}

/**
	propagacja sygna³u b³êdu serwera; emituje odpowiedni sygna³
*/
void Connection::clientServErr(){
    serverDisconnected(DISC);
}
/**
	propagacja sygna³u otrzymania wektora raportów od serwera; metoda sygnalizuje gdy wektor jest gotowy poprzez sygna³
*/
void Connection::clientNewRapVec(){
    raportsVectorReady(QVector<pRaport>::fromStdVector(giveRaportsFromServer()));
}



