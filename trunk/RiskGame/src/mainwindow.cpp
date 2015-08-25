#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Logger(ui->logger);

    ui->endTurnButton->setEnabled(false);

    connect(ui->actionCreateGAme, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->actionJoinGame, SIGNAL(triggered()), this, SLOT(connectToGame()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->endTurnButton, SIGNAL(clicked()), this, SLOT(endTurn()));

    connect(ui->graphicsView, SIGNAL(showTerritoryInfo(int)), this, SLOT(showTerritoryInfo(int)));
    connect(ui->graphicsView, SIGNAL(hideTerritoryInfo()), this, SLOT(hideTerritoryInfo()));

    connect(ui->graphicsView, SIGNAL(updateStatusBar()), this, SLOT(updateStatusBar()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::startNewGame(){
    CreateGameDialog d;

    if(d.exec()){
        ui->graphicsView->start();
        ui->endTurnButton->setEnabled(true);
        Player::getInstance().setName("Server");
        Player::getInstance().setServer(true);
		Player::getInstance().setId(PLAYER1);
        ui->statusBar->show();
        updateStatusBar();
        ui->actionCreateGAme->setEnabled(false);
        ui->actionJoinGame->setEnabled(false);
		connect(  &Connection::getInstance(), SIGNAL(clientDisconnected(EndGameId)), this, SLOT(endGame(EndGameId)) );
		
    }
}

void MainWindow::connectToGame(){
    JoinGameDialog d;
    if(d.exec()){
		qDebug() << "[Connected - "<< Connection::getInstance().getMapName() << " - 1: " << Connection::getInstance().getPlayersPosition().first << " - 2: " << Connection::getInstance().getPlayersPosition().second << " ]";
		Map::getInstance().loadMap(Connection::getInstance().getMapName());
		Map::getInstance().setPlayerStartingPosition(PLAYER1, Connection::getInstance().getPlayersPosition().first);
		Map::getInstance().setPlayerStartingPosition(PLAYER2, Connection::getInstance().getPlayersPosition().second);
        ui->graphicsView->start();
        ui->endTurnButton->setEnabled(true);
        Player::getInstance().setName("Client");
		Player::getInstance().setId(PLAYER2);
        ui->statusBar->show();
        updateStatusBar();
        ui->actionCreateGAme->setEnabled(false);
        ui->actionJoinGame->setEnabled(false);
		connect(  &Connection::getInstance(), SIGNAL(serverDisconnected(EndGameId)), this, SLOT(endGame(EndGameId)) );
    }
}

void MainWindow::quit(){
    close();
}



void MainWindow::endTurn(){
    ui->endTurnButton->setEnabled(false);
    RaportDialog d;
    
    if(d.exec()){
        checkVictory();
	    ui->endTurnButton->setEnabled(true);
        updateStatusBar();
    } else {
        endGame(LOST);
    }
    
}

void MainWindow::showTerritoryInfo(int id){
    ui->territoryInfoLabel->showTerritoryInfo(id);
}

void MainWindow::hideTerritoryInfo(){
    ui->territoryInfoLabel->hideTerritoryInfo();
}

void MainWindow::updateStatusBar(){
    ui->statusBar->update();
}

void MainWindow::checkVictory(){
    switch(Player::getInstance().id()){
        case PLAYER1:
            if(Map::getInstance().getPlayerTerritories(PLAYER1).size() == 0)
                endGame(LOST);
            if(Map::getInstance().getPlayerTerritories(PLAYER2).size() == 0)
                endGame(WON);
            
            break;
        case PLAYER2:
            if(Map::getInstance().getPlayerTerritories(PLAYER2).size() == 0)
                endGame(LOST);
            if(Map::getInstance().getPlayerTerritories(PLAYER1).size() == 0)
                endGame(WON);
            
            break;
    }    
}

void MainWindow::endGame(EndGameId id){
    RaportDialog d;
    switch(id){
        case WON:
        d.write("Congratulations!!!\nYou have WON!");break;
        case LOST:
        d.write("You have LOST\nBetter luck next time!");break;
        case DISC:
        d.write("Enemy has disconnected. You WON!!!");break;
    }
    d.write("Goodbye");
    d.exec();
    close();
}