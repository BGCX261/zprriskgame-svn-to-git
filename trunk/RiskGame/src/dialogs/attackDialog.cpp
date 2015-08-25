#include "dialogs/attackDialog.h"
#include "ui_attackdialog.h"


AttackDialog::AttackDialog(QWidget *parent, pTerritory fromTerritory, pTerritory toTerritory)
: QDialog(parent)
, fromTerritory_(fromTerritory)
, toTerritory_(toTerritory)
, ui(new Ui::AttackDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setText(QString("You're attacking from ")
        .append(fromTerritory_->name()).append(" to ").append(toTerritory_->name()));

    ui->availableTable->setColumnCount(2);
    ui->availableTable->setColumnWidth(0,50);
    ui->availableTable->setColumnWidth(1,19);
    ui->availableTable->setRowCount(NO_UNITS);
    ui->availableTable->verticalHeader()->hide();
    ui->availableTable->horizontalHeader()->hide();
    ui->availableTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->availableTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availableTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->availableTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

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

    for(int i=0; i<NO_UNITS; i++){
        ui->availableTable->hideRow(i);
        ui->chosenTable->hideRow(i);
    }

    
    for(int i=0; i<fromTerritory_->units().size(); i++){
        pUnit unit = fromTerritory_->units()[i];
        //QTableWidgetItem *type = new QTableWidgetItem(QString::number(unit->type()));
        QTableWidgetItem *name = new QTableWidgetItem(unit->name());
        QTableWidgetItem *n = new QTableWidgetItem(QString::number(unit->noUnits()));

        //ui->availableTable->setItem(i,0,type);
        int nn = unit->type();
        ui->availableTable->setItem(nn,0,name);
        ui->availableTable->setItem(nn,1,n);
        ui->availableTable->showRow(nn);
    }

    if(toTerritory_->isVisible()){
        ui->noUnitsLabel->setText(QString::number(toTerritory_->noUnits()));
        ui->bunkerLabel->setText(toTerritory_->hasBuilding(BUNKER)?"yes":"no");
        ui->watchtowerLabel->setText(toTerritory_->hasBuilding(WATCHTOWER)?"yes":"no");
    }


    connect(ui->availableTable, SIGNAL(cellClicked(int,int)), this, SLOT(availRowSelected(int,int)));
    connect(ui->chosenTable, SIGNAL(cellClicked(int,int)), this, SLOT(chosRowSelected(int,int)));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
    connect(ui->addAllButton, SIGNAL(clicked()), this, SLOT(addAllClicked()));

    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(remClicked()));
    connect(ui->removeAllButton, SIGNAL(clicked()), this, SLOT(remAllClicked()));

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
        
}

AttackDialog::~AttackDialog()
{
    delete ui;
}

void AttackDialog::addClicked(){
    if(ui->availableTable->selectedItems().size() != 0){
        int id = ui->availableTable->selectedItems()[0]->row();
        move(id, *ui->availableTable, *ui->chosenTable, 1);
    }
}

void AttackDialog::remClicked(){
    if(ui->chosenTable->selectedItems().size() != 0){
        int id = ui->chosenTable->selectedItems()[0]->row();
        move(id, *ui->chosenTable, *ui->availableTable, 1);
    }
}

void AttackDialog::addAllClicked(){
    for(int i=0; i<NO_UNITS; i++){
        move(i, *ui->availableTable, *ui->chosenTable, 0);
    }
}

void AttackDialog::remAllClicked(){
    for(int i=0; i<NO_UNITS; i++){
        move(i, *ui->chosenTable, *ui->availableTable, 0);
    }
}

void AttackDialog::move(int id, QTableWidget& from, QTableWidget& to, int n){

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

void AttackDialog::accepted() {
    for(int i=0; i<NO_UNITS; i++){
        QTableWidgetItem* item;
        if((item = ui->chosenTable->item(i,1))){
            int noUnits = item->text().toInt();
            fromTerritory_->removeUnit(UnitsId(i), noUnits);
            pCommand c(CommandsFactory::getInstance().create(ATTACK_COMMAND,
                fromTerritory_->id(), toTerritory_->id(), i, noUnits));
            Player::getInstance().addCommand(c);
        }

    }
}