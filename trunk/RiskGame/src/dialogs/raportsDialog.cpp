#include "dialogs/raportsDialog.h"
#include "ui_raportsdialog.h"

#include <QPushButton>

RaportsDialog::RaportsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaportDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    /*connect(&Calculator::getInstance(), SIGNAL(preparedRaports(raportVect)),
        this, SLOT(raports(raportVect)));
    connect(&Calculator::getInstance(), SIGNAL(receivedAllCommands()),
        this, SLOT(allPlayers()));*/
}

RaportsDialog::~RaportsDialog()
{
    delete ui;
}

//void RaportsDialog::allPlayers(){
//    write("All players had send commands");
//}
//
//void RaportsDialog::raports(raportVect v){
//    write("Interpreting raports...");
//    Interpreter::getInstance().applyRaports(v);
//
//    foreach(QString s, Interpreter::getInstance().info())
//        write(s);
//
//    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
//}

void RaportsDialog::write(QString s){
    ui->textBrowser->setPlainText(ui->textBrowser->toPlainText().append(s).append("\n"));
}