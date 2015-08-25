#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

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
    class MoveDialog;
}

class MoveDialog : public QDialog {
    Q_OBJECT
public:
    MoveDialog(QWidget *parent, pTerritory fromTerritory, pTerritory toTerritory);
    ~MoveDialog();

protected:

private slots:
    void moveRightClicked();
    void moveLeftClicked();
    void moveAllRightClicked();
    void moveAllLeftClicked();

    void reset();
    void accepted();

private:

    void move(int id, QTableWidget& from, QTableWidget& to, int n = 1);

    Ui::MoveDialog *ui;

    pTerritory fromTerritory_;
    pTerritory toTerritory_;
};

#endif // 