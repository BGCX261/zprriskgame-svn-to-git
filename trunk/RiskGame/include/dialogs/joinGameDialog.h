#ifndef JOINGAMEDIALOG_H
#define JOINGAMEDIALOG_H

#include <QDialog>

#include "connection/connection.h"

namespace Ui {
    class JoinGameDialog;
}

class JoinGameDialog : public QDialog {
    Q_OBJECT
public:
    JoinGameDialog(QWidget *parent = 0);
    ~JoinGameDialog();

protected:

private slots:
    void join();
private:

    Ui::JoinGameDialog *ui;
};

#endif // 