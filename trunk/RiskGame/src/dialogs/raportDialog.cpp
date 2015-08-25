#include "dialogs/raportdialog.h"
#include "ui_raportsdialog.h"

#include <QPushButton>

RaportDialog::RaportDialog(QWidget *parent, bool endGameDialog) :
    QDialog(parent),
    ui(new Ui::RaportDialog)
{
    ui->setupUi(this);

    if(endGameDialog){
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

	    if(Player::getInstance().isServer())
	    {
		    // akcje dla servera
		    write("Waiting for commands from client...");
            connect(&Calculator::getInstance(), SIGNAL(preparedRaports(raportVect)),this, SLOT(raports(raportVect)));
		    connect(&Calculator::getInstance(), SIGNAL(receivedAllCommands()),this, SLOT(allPlayers()));
		    Calculator::getInstance().addCommands(Player::getInstance().getCommandsAndReset());
	    }
	    else
	    {
		    // akcje dla klienta
            write("Commands sent to server and waiting...");
            connect(&Connection::getInstance(), SIGNAL(raportsVectorReady(raportVect)),this, SLOT( raports(raportVect)));
		    Connection::getInstance().sendCommandsToServer(Player::getInstance().getCommandsAndReset().toStdVector());
	    }
    }
}

RaportDialog::~RaportDialog()
{
    delete ui;
}

void RaportDialog::allPlayers(){
    write("All players had send commands");
}

void RaportDialog::raports(raportVect v){
    write("Interpreting raports...");
	if(Player::getInstance().isServer())
	{
		Connection::getInstance().sendRaportsToClient(v.toStdVector());
	}
    Interpreter::getInstance().applyRaports(v);

    foreach(QString s, Interpreter::getInstance().info())
        write(s);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
	
}


void RaportDialog::write(QString s){
    ui->textBrowser->setPlainText(ui->textBrowser->toPlainText().append(s).append("\n"));
}
