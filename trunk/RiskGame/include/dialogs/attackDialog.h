#ifndef ATTACKDIALOG_H
#define ATTACKDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include "commands/command.h"
#include "commands/commandsFactory.h"
#include "territories/territory.h"
#include "units/unit.h"
#include "units/infantry.h"
#include "units/tank.h"
#include "utils/ids.h"
#include "utils/logger.h"
#include "utils/singleton.h"
#include "utils/defs.h"

#include <boost/shared_ptr.hpp>

namespace Ui {
    class AttackDialog;
}

class AttackDialog : public QDialog {
    Q_OBJECT
public:
    AttackDialog(QWidget *parent, pTerritory fromTerritory, pTerritory toTerritory);
    ~AttackDialog();

protected:

private slots:
        void addClicked();
        void remClicked();
        void addAllClicked();
        void remAllClicked();

        void accepted();

private:

    void addUnit(QString id);
    void removeUnit(QString id);

    void move(int id, QTableWidget& from, QTableWidget& to, int n = 1);

    Ui::AttackDialog *ui;

    pTerritory fromTerritory_;
    pTerritory toTerritory_;
};

#endif // 