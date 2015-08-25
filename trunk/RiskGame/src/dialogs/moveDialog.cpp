#include "dialogs/moveDialog.h"
#include "ui_movedialog.h"

MoveDialog::MoveDialog(QWidget *parent, pTerritory fromTerritory, pTerritory toTerritory)
: QDialog(parent)
, fromTerritory_(fromTerritory)
, toTerritory_(toTerritory)
, ui(new Ui::MoveDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setText(QString("You're moving between ")
        .append(fromTerritory_->name()).append(" to ").append(toTerritory_->name()));

    ui->leftTable->setColumnCount(2);
    ui->leftTable->setColumnWidth(0,50);
    ui->leftTable->setColumnWidth(1,19);
    ui->leftTable->setRowCount(NO_UNITS);
    ui->leftTable->verticalHeader()->hide();
    ui->leftTable->horizontalHeader()->hide();
    ui->leftTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->leftTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->leftTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->leftTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui->rightTable->setColumnCount(2);
    ui->rightTable->setColumnWidth(0,50);
    ui->rightTable->setColumnWidth(1,19);
    ui->rightTable->setRowCount(NO_UNITS);
    ui->rightTable->verticalHeader()->hide();
    ui->rightTable->horizontalHeader()->hide();
    ui->rightTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rightTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rightTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->rightTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);


    reset();

    connect(ui->leftTable, SIGNAL(cellClicked(int,int)), this, SLOT(leftRowSelected(int,int)));
    connect(ui->rightTable, SIGNAL(cellClicked(int,int)), this, SLOT(rightRowSelected(int,int)));

    connect(ui->moveRightButton, SIGNAL(clicked()), this, SLOT(moveRightClicked()));
    connect(ui->moveAllRightButton, SIGNAL(clicked()), this, SLOT(moveAllRightClicked()));

    connect(ui->moveLeftButton, SIGNAL(clicked()), this, SLOT(moveLeftClicked()));
    connect(ui->moveAllLeftButton, SIGNAL(clicked()), this, SLOT(moveAllLeftClicked()));

    connect(ui->backToStartButton, SIGNAL(clicked()), this, SLOT(reset()));

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
        
}

MoveDialog::~MoveDialog()
{
    delete ui;
}

void MoveDialog::moveRightClicked(){
    if(ui->leftTable->selectedItems().size() != 0){
        int id = ui->leftTable->selectedItems()[0]->row();
        move(id, *ui->leftTable, *ui->rightTable, 1);
    }
}

void MoveDialog::moveLeftClicked(){
    if(ui->rightTable->selectedItems().size() != 0){
        int id = ui->rightTable->selectedItems()[0]->row();
        move(id, *ui->rightTable, *ui->leftTable, 1);
    }
}

void MoveDialog::moveAllRightClicked(){
    for(int i=0; i<NO_UNITS; i++){
        move(i, *ui->leftTable, *ui->rightTable, 0);
    }
}

void MoveDialog::moveAllLeftClicked(){
    for(int i=0; i<NO_UNITS; i++){
        move(i, *ui->rightTable, *ui->leftTable, 0);
    }
}

void MoveDialog::move(int id, QTableWidget& from, QTableWidget& to, int n){

    QTableWidgetItem* f = from.item(id,1);

    if(!f)
        return;

    int fn = f->text().toInt();
    QTableWidgetItem* t = to.item(id,1);

    if(n == 0)
        n = fn;

    if(t){
        t->setText(QString::number(n + t->text().toInt()));
    } else {
        QTableWidgetItem *name = new QTableWidgetItem(*from.item(id,0));
        QTableWidgetItem *nn = new QTableWidgetItem(QString::number(n));

        to.setItem(id,0,name);
        to.setItem(id,1,nn);
        to.showRow(id);
    }

    if(fn-n > 0){
        f->setText(QString::number(fn-n));
    } else {
        delete from.item(id,0);
        delete from.item(id,1);
        from.hideRow(id);
    }
}

void MoveDialog::accepted() {
    for(int i=0; i<NO_UNITS; i++){
        QTableWidgetItem* item;
        int diff;

        if((item = ui->leftTable->item(i,1))){
            diff = fromTerritory_->noUnits(UnitsId(i)) - item->text().toInt();
        } else {
            diff = fromTerritory_->noUnits(UnitsId(i));
        }

        if(diff > 0){
            fromTerritory_->removeUnit(UnitsId(i), diff);
            pCommand c(CommandsFactory::getInstance().create(MOVE_COMMAND,
            fromTerritory_->id(), toTerritory_->id(), i, diff));
            Player::getInstance().addCommand(c);
        }

        if((item = ui->rightTable->item(i,1))){
            diff = toTerritory_->noUnits(UnitsId(i)) - item->text().toInt();
        } else {
            diff = toTerritory_->noUnits(UnitsId(i));
        }

        if(diff > 0){
            toTerritory_->removeUnit(UnitsId(i), diff);
            pCommand c(CommandsFactory::getInstance().create(MOVE_COMMAND,
            toTerritory_->id(), fromTerritory_->id(), i, diff));
            Player::getInstance().addCommand(c);
        }
    }
}

void MoveDialog::reset(){
    ui->leftTable->clear();
    ui->rightTable->clear();

    for(int i=0; i<NO_UNITS; i++){
        ui->leftTable->hideRow(i);
        ui->rightTable->hideRow(i);
    }

    
    for(int i=0; i<fromTerritory_->units().size(); i++){
        pUnit unit = fromTerritory_->units()[i];
        QTableWidgetItem *name = new QTableWidgetItem(unit->name());
        QTableWidgetItem *n = new QTableWidgetItem(QString::number(unit->noUnits()));

        int nn = unit->type();
        ui->leftTable->setItem(nn,0,name);
        ui->leftTable->setItem(nn,1,n);
        ui->leftTable->showRow(nn);
    }

    for(int i=0; i<toTerritory_->units().size(); i++){
        pUnit unit = toTerritory_->units()[i];
        QTableWidgetItem *name = new QTableWidgetItem(unit->name());
        QTableWidgetItem *n = new QTableWidgetItem(QString::number(unit->noUnits()));

        int nn = unit->type();
        ui->rightTable->setItem(nn,0,name);
        ui->rightTable->setItem(nn,1,n);
        ui->rightTable->showRow(nn);
    }
}

