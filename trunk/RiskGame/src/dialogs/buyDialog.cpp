#include "dialogs/buyDialog.h"
#include "ui_buydialog.h"

BuyDialog::BuyDialog(QWidget *parent, pTerritory territory) :
    QDialog(parent),
    ui(new Ui::BuyDialog),
    territory_(territory),
    money_(Player::getInstance().money())
    , cost_(0)
{
    ui->setupUi(this);
    ui->titleLabel->setText(QString("Buying for ").append(territory_->name()));

    ui->moneyLabel->setText(QString::number(money_));

    ui->buyTable->setColumnCount(4);
    /*ui->buyTable->setColumnWidth(0,50);
    ui->buyTable->setColumnWidth(1,19);*/
    ui->buyTable->setRowCount(NO_UNITS);
    ui->buyTable->verticalHeader()->hide();
    ui->buyTable->horizontalHeader()->hide();
    ui->buyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->buyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->buyTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->buyTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui->chosenTable->setColumnCount(2);
    ui->chosenTable->setColumnWidth(0,50);
    ui->chosenTable->setColumnWidth(1,19);
    ui->chosenTable->setRowCount(NO_UNITS);
    ui->chosenTable->verticalHeader()->hide();
    ui->chosenTable->horizontalHeader()->hide();
    ui->chosenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->chosenTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->chosenTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->chosenTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui->buyTable2->setColumnCount(2);
    ui->buyTable2->setRowCount(NO_BUILDINGS);
    ui->buyTable2->verticalHeader()->hide();
    ui->buyTable2->horizontalHeader()->hide();
    ui->buyTable2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->buyTable2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->buyTable2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->buyTable2->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui->chosenTable2->setColumnCount(1);
    ui->chosenTable2->setRowCount(NO_BUILDINGS);
    ui->chosenTable2->verticalHeader()->hide();
    ui->chosenTable2->horizontalHeader()->hide();
    ui->chosenTable2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->chosenTable2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->chosenTable2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->chosenTable2->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui->territoryTable->setRowCount(NO_UNITS);
    ui->territoryTable->setColumnCount(2);
    ui->territoryTable->verticalHeader()->hide();
    ui->territoryTable->horizontalHeader()->hide();
    ui->territoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->territoryTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui->territoryTable2->setRowCount(NO_BUILDINGS);
    ui->territoryTable2->setColumnCount(1);
    ui->territoryTable2->verticalHeader()->hide();
    ui->territoryTable2->horizontalHeader()->hide();
    ui->territoryTable2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->territoryTable2->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);


    setAll();

    connect(ui->buyTable, SIGNAL(cellClicked(int,int)), this, SLOT(unitsLeftRowSelected()));
    connect(ui->chosenTable, SIGNAL(cellClicked(int,int)), this, SLOT(unitsRightRowSelected()));

    connect(ui->buyTable2, SIGNAL(cellClicked(int,int)), this, SLOT(buildingsLeftRowSelected()));
    connect(ui->chosenTable2, SIGNAL(cellClicked(int,int)), this, SLOT(buildingsRightRowSelected()));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeClicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->buyButton, SIGNAL(clicked()), this, SLOT(buyClicked()));

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
}

BuyDialog::~BuyDialog()
{
    delete ui;
}

void BuyDialog::unitsLeftRowSelected(){
    ui->buyTable2->clearSelection();
}

void BuyDialog::unitsRightRowSelected(){
    ui->chosenTable2->clearSelection();
}

void BuyDialog::buildingsLeftRowSelected(){
    ui->buyTable->clearSelection();
}

void BuyDialog::buildingsRightRowSelected(){
    ui->chosenTable->clearSelection();
}

void BuyDialog::addClicked(){
    if(ui->buyTable->selectedItems().size() > 0){
        int id = ui->buyTable->selectedItems()[0]->row();
        buyUnit(id);
    } else
    if(ui->buyTable2->selectedItems().size() > 0){
        int id = ui->buyTable2->selectedItems()[0]->row();
        buyBuilding(id);
    }

    updateCost();
}

void BuyDialog::removeClicked(){
    if(ui->chosenTable->selectedItems().size() > 0){
        int id = ui->chosenTable->selectedItems()[0]->row();
        removeUnit(id);
    } else
    if(ui->chosenTable2->selectedItems().size() > 0){
        int id = ui->chosenTable2->selectedItems()[0]->row();
        removeBuilding(id);
    }
    updateCost();
}

void BuyDialog::clearClicked(){
    resetBuys();
}

void BuyDialog::buyClicked(){
    applyBuys();
    resetBuys();
}

void BuyDialog::buyUnit(int id, int n){
    QTableWidgetItem* f = ui->buyTable->item(id,1);

    if(!f)
        return;

    if(money_ - cost_ - UNITS_COST[id] < 0)
        return;
    cost_+=UNITS_COST[id];

    QTableWidgetItem* t = ui->chosenTable->item(id,1);

    if(t){
        t->setText(QString::number(n + t->text().toInt()));
    } else {
        QTableWidgetItem *name = new QTableWidgetItem(*ui->buyTable->item(id,0));
        ui->chosenTable->setItem(id,0,name);
        QTableWidgetItem *nn = new QTableWidgetItem(QString::number(n));
        ui->chosenTable->setItem(id,1,nn);
        ui->chosenTable->showRow(id);
    }
}

void BuyDialog::removeUnit(int id, int n){
    QTableWidgetItem* f = ui->chosenTable->item(id,1);
    if(!f)
        return;

    cost_-=UNITS_COST[id];

    int fn = f->text().toInt();
    if(fn == 1){
        delete ui->chosenTable->item(id,0);
        delete ui->chosenTable->item(id,1);
        ui->chosenTable->hideRow(id);
    } else {
        f->setText(QString::number(f->text().toInt() - n));
    }
}

void BuyDialog::buyBuilding(int id){
    QTableWidgetItem* f = ui->buyTable2->item(id,1);

    if(!f)
        return;

    if(money_ - cost_ - BUILDINGS_COST[id] < 0)
        return;
    cost_+=BUILDINGS_COST[id];

    QTableWidgetItem *name = new QTableWidgetItem(*ui->buyTable2->item(id,0));
    ui->chosenTable2->setItem(id,0,name);
    ui->chosenTable2->showRow(id);
    ui->buyTable2->hideRow(id);
}

void BuyDialog::removeBuilding(int id){
    QTableWidgetItem* f = ui->chosenTable2->item(id,0);

    if(!f)
        return;

    cost_-=BUILDINGS_COST[id];

    delete f;
    ui->chosenTable2->hideRow(id);
    ui->buyTable2->showRow(id);
}

void BuyDialog::resetBuys(){
    ui->chosenTable->clear();
    ui->chosenTable2->clear(); 

    for(int i=0; i<NO_UNITS; i++){
        ui->chosenTable->hideRow(i);
    }

    for(int i=0; i<NO_BUILDINGS; i++){
        ui->chosenTable2->hideRow(i);
        if(!territory_->hasBuilding(BuildingsId(i)))
            ui->buyTable2->showRow(i);
    }

    cost_ = 0;
    updateCost();
}

void BuyDialog::setTerritoryInfo(){
    
    for(int i=0; i<NO_UNITS; i++){
        ui->territoryTable->hideRow(i);
        int noUnits = territory_->noUnits(UnitsId(i));
        if(noUnits <=0)
            continue;

        QTableWidgetItem *name = new QTableWidgetItem(UNITS_NAME[i]);
        QTableWidgetItem *n = new QTableWidgetItem(QString::number(noUnits));

        ui->territoryTable->setItem(i,0,name);
        ui->territoryTable->setItem(i,1,n);
        ui->territoryTable->showRow(i);
    }

    for(int i=0; i<NO_BUILDINGS; i++){
        ui->territoryTable2->hideRow(i);
        bool has = territory_->hasBuilding(BuildingsId(i));
        if(!has)
            continue;

        QTableWidgetItem *name = new QTableWidgetItem(BUILDINGS_NAME[i]);

        ui->territoryTable2->setItem(i,0,name);
        ui->territoryTable2->showRow(i);
    }
}


void BuyDialog::setAll(){

    for(int i=0; i<NO_UNITS; i++){
        QTableWidgetItem *name = new QTableWidgetItem(UNITS_NAME[i]);
        QTableWidgetItem *cost = new QTableWidgetItem(QString::number(UNITS_COST[i]));
        QTableWidgetItem *attack = new QTableWidgetItem(QString::number(UNITS_ATTACK[i]));
        QTableWidgetItem *defence = new QTableWidgetItem(QString::number(UNITS_DEFENCE[i]));

        ui->buyTable->setItem(i,0,name);
        ui->buyTable->setItem(i,1,cost);
        ui->buyTable->setItem(i,2,attack);
        ui->buyTable->setItem(i,3,defence);

        ui->chosenTable->hideRow(i);
    }

    for(int i=0; i<NO_BUILDINGS; i++){
        QTableWidgetItem *name = new QTableWidgetItem(BUILDINGS_NAME[i]);
        QTableWidgetItem *cost = new QTableWidgetItem(QString::number(BUILDINGS_COST[i]));

        ui->buyTable2->setItem(i,0,name);
        ui->buyTable2->setItem(i,1,cost);
        if(territory_->hasBuilding(BuildingsId(i)))
            ui->buyTable2->hideRow(i);

        ui->chosenTable2->hideRow(i);
    }

    resetBuys();
    setTerritoryInfo();
}

void BuyDialog::applyBuys(){
    for(int i=0; i<NO_UNITS; i++){
        QTableWidgetItem* f = ui->chosenTable->item(i,0);

        if(!f)
            continue;

        int n =  ui->chosenTable->item(i,1)->text().toInt();

        buyCommands_.push_back(pCommand(CommandsFactory::getInstance().create(
            BUILD_COMMAND, territory_->id(), UNIT, i, n)));
    }

    for(int i=0; i<NO_BUILDINGS; i++){
        QTableWidgetItem* f = ui->chosenTable2->item(i,0);

        if(!f)
            continue;

        buyCommands_.push_back(pCommand(CommandsFactory::getInstance().create(
            BUILD_COMMAND, territory_->id(), BUILDING, i,1)));
    }

    money_-=cost_;
    cost_ = 0;
    updateCost();
    updateMoney();    
}

void BuyDialog::accepted(){
    Player::getInstance().addCommands(buyCommands_);
    Player::getInstance().setMoney(money_);
}

void BuyDialog::updateCost(){
    ui->costLabel->setText(QString::number(cost_));
}

void BuyDialog::updateMoney(){
    ui->moneyLabel->setText(QString::number(money_));
}