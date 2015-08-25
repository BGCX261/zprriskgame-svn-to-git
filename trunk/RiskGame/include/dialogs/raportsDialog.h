    #ifndef RAPORTSDIALOG_H
#define RAPORTSDIALOG_H

#include <QDialog>

#include "utils/defs.h"
#include "calculator/interpreter.h"
#include "calculator/calculator.h"

namespace Ui {
    class RaportDialog;
}

class RaportsDialog : public QDialog {
    Q_OBJECT
public:
    RaportsDialog(QWidget *parent = 0);
    ~RaportsDialog();

protected:

private slots:
    /*void allPlayers();
    void raports(raportVect v);*/
private:
    void write(QString s);
    Ui::RaportDialog *ui;
};

#endif // 