#include "dialogs/createGameDialog.h"
#include "ui_creategamedialog.h"

#include <QPushButton>

CreateGameDialog::CreateGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGameDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    Map::getInstance().loadMap("riskmap.xml");
    Map::getInstance().randomizeStartingPositions();

    connect(ui->createServerButton, SIGNAL(clicked()), this, SLOT(create()));
}

CreateGameDialog::~CreateGameDialog()
{
    delete ui;
}

void CreateGameDialog::create(){
    if(Connection::getInstance().createServer()){
        ui->infoLabel->setText(
            QString("Server created at\n").append(
            Connection::getInstance().getAddress().append(":").append(
            Connection::getInstance().getPort())));
        ui->statusLabel->setText("Waiting for client...");
		connect(  &Connection::getInstance(), SIGNAL(clientConnected()), this, SLOT(created()) );
    } else {
        ui->infoLabel->setText("Cannot create server!");
    }
}

void CreateGameDialog::created(){
	ui->statusLabel->setText("Client connected");
	Connection::getInstance().sendMap(QString("riskmap.xml"),Map::getInstance().playerStartingPosition(PLAYER1),Map::getInstance().playerStartingPosition(PLAYER2));
	connect(&Connection::getInstance(), SIGNAL(commandsVectorReady()),&Calculator::getInstance(), SLOT(commandsReceived()));
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}