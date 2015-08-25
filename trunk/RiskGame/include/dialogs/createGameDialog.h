#ifndef CREATEGAMEDIALOG_H
#define CREATEGAMEDIALOG_H

#include <QDialog>

#include "connection/connection.h"
#include "calculator/calculator.h"
#include "map.h"

namespace Ui {
    class CreateGameDialog;
}

class CreateGameDialog : public QDialog {
    Q_OBJECT
public:
    CreateGameDialog(QWidget *parent = 0);
    ~CreateGameDialog();
public slots:
	void created();
protected:

private slots:
        void create();

private:

    Ui::CreateGameDialog *ui;
};

#endif // 