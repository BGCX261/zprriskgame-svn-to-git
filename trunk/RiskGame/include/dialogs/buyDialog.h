#ifndef BUYDIALOG_H
#define BUYDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

#include "player/player.h"
#include "commands/command.h"
#include "commands/commandsFactory.h"
#include "territories/territory.h"
#include "units/unit.h"
#include "units/infantry.h"
#include "units/tank.h"
#include "buildings/building.h"
#include "buildings/bunker.h"
#include "buildings/watchtower.h"
#include "buildings/factory.h"
#include "utils/ids.h"
#include "utils/logger.h"
#include "utils/singleton.h"
#include "utils/defs.h"

namespace Ui {
    class BuyDialog;
}

class BuyDialog : public QDialog {
    Q_OBJECT
public:
    BuyDialog(QWidget *parent, pTerritory territory);
    ~BuyDialog();

protected:

private slots:

    void unitsLeftRowSelected();
    void unitsRightRowSelected();
    void buildingsLeftRowSelected();
    void buildingsRightRowSelected();

    void addClicked();
    void removeClicked();
    void clearClicked();
    void buyClicked();

    
    void accepted();

private:


    void setAll();
    void resetBuys();
    void setTerritoryInfo();

    void applyBuys();

    void buyUnit(int id, int n = 1);
    void removeUnit(int id, int n=1);

    void buyBuilding(int id);
    void removeBuilding(int id);

    void updateCost();
    void updateMoney();

    Ui::BuyDialog *ui;

    pTerritory territory_;
    commandVect buyCommands_;
    int money_;
    int cost_;
};

#endif // 