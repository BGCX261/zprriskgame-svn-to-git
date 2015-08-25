#ifndef RAPORTFIALOG_H
#define RAPORTFIALOG_H

#include <QDialog>

#include "utils/defs.h"
#include "calculator/interpreter.h"
#include "calculator/calculator.h"
#include "connection/connection.h"

namespace Ui {
    class RaportDialog;
}

class RaportDialog : public QDialog {
    Q_OBJECT
public:
    RaportDialog(QWidget *parent = 0, bool endGameDialog = false);
    ~RaportDialog();
    void write(QString s);
private slots:
    void allPlayers();
	//void commandsReceived();
    void raports(raportVect v);
private:
    
    Ui::RaportDialog *ui;
};

#endif // 