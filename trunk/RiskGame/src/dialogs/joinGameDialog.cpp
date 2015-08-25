#include "dialogs/joinGameDialog.h"
#include "ui_joingamedialog.h"

#include <QPushButton>

JoinGameDialog::JoinGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinGameDialog)
{
    ui->setupUi(this);
    ui->addressLine->setText("127.0.0.1");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->joinButton, SIGNAL(clicked()), this, SLOT(join()));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

JoinGameDialog::~JoinGameDialog()
{
    delete ui;
}

void JoinGameDialog::join(){
	if(Connection::getInstance().conn(ui->addressLine->displayText(),
        ui->portLine->displayText())){
		ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
		ui->statusLabel->setText("Connected!");
    } else {
        ui->statusLabel->setText("Couldn't connect!");
    }
}