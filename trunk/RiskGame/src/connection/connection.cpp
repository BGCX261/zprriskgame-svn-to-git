
#include "connection/connection.h"

/**
	metoda tworzy nowy serwer, je�li operacja si� powiedzie zwraca true, w przeciwnym razie false
	@return flaga oznaczaj�ca czy serwer wystartowa�
*/
bool Connection::createServer(){
	//tworze 
        server=new Server();

        //connect wy��cznie je�li uda�o mi si� stworzy� serwer
        if(server->isServerCreated()){
            connect(reinterpret_cast<QObject*>(server), SIGNAL(newClientConnected()),
                    this, SLOT(servNewCon()));
        }
    return server->isServerCreated();

}
/**
	metoda tworzy klienta, kt�ry ��czy si� w momencie tworzenia z podanym serwerem, 
	je�li operacja si� powiedzie zwraca true, w przeciwnym razie false
	@param address - okre�la adres IP z jakim klient spr�buje si� po��czy�
	@param port - okre�la port z jakim klient spr�buje si� po��czy�
	@return flaga oznaczaj�ca czy uda�o si� po��czy� z hostem
*/
bool Connection::conn(QString address, QString port){
	//tworze, wewn�trz konstruktora jest te� pr�ba ��czenia
        client = new Client(address,port);
		//sygna�y je�li si� po��czy�em
        if(client->isConnectedToServer()){
            connect(reinterpret_cast<QObject*>(client), SIGNAL(hostDisconnected()), this, SLOT(clientServErr()));
            connect(reinterpret_cast<QObject*>(client), SIGNAL(receivedRaports()), this, SLOT(clientNewRapVec()));
        }
        return client->isConnectedToServer();
}
/**
	metoda zwraca pierwszy z listy interfejs�w sieciowych komputera, nasluchujacy adres ip i nie jest to interfejs loopback; 
	@return adres IPv4 na jakim nas�uchuje serwer (jako QString)
*/
QString Connection::getAddress(){
    //zwraca pierwszy nasluchujacy ip i nie loopback
    return server->getServerIp();
}
/**
	metoda zwraca wylosowany port na kt�rym s�ucha serwer 
	@return port na jakim serwer nas�uchuje
*/
QString Connection::getPort(){
    return server->getServerPort();
}

/**
	metoda zwraca wektor komand (dok�adnie to wektor shared_ptr<Command>), kt�re zosta�y pobrane od klienta
	@return wektor komend (std::vector<pCommand>)
*/
std::vector<pCommand> Connection::giveCommandsFromClient(){

    return server->getReadyCommandsVector();
}

//////sloty
/**
	metoda-slot, wo�ana, gdy pod��cza si� nowy klient (powoduje pod��czenie odpowiednich sygna��w do slot�w i emisj� clientConnected())
*/
void Connection::servNewCon(){
    connect(reinterpret_cast<QObject*>(server), SIGNAL(newVectorHasBeenReceived()),
            this, SLOT(servNewComVec()));
    connect(reinterpret_cast<QObject*>(server), SIGNAL(errorClientDisconnected()),
            this, SLOT(servClientErr()));
    clientConnected(); //sygnal
}

/**
	propagacja sygna�u otrzymania wektora komend od klienta; metoda sygnalizuje gdy wektor jest gotowy poprzez sygna�
*/
void Connection::servNewComVec(){
    commandsVectorReady(); //sygnal
}
/**
	propagacja sygna�u b��du klienta; metoda sygnalizuje poprzez emisj� sygna�u
*/
void Connection::servClientErr(){
    clientDisconnected(DISC); //sygnal
}

/**
	propagacja sygna�u b��du serwera; emituje odpowiedni sygna�
*/
void Connection::clientServErr(){
    serverDisconnected(DISC);
}
/**
	propagacja sygna�u otrzymania wektora raport�w od serwera; metoda sygnalizuje gdy wektor jest gotowy poprzez sygna�
*/
void Connection::clientNewRapVec(){
    raportsVectorReady(QVector<pRaport>::fromStdVector(giveRaportsFromServer()));
}



