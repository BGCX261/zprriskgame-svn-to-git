#include "mapview.h"

#include <ui_attackDialog.h>

#include "buildings/watchtower.h"
#include "buildings/bunker.h"

MapView::MapView(QWidget* widget)
    : QGraphicsView(widget)
    , selectedTerritory1_(NULL)
    , pointedTerritory_(NULL)
{
    initActions();
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setMouseTracking(true);
}

void MapView::start(){

    Map& map = Map::getInstance();

    QGraphicsScene* scene = new QGraphicsScene();
    setSceneRect(0,0,798,399);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QVector<TerritoriesConnection*> connVect;

    Map::getInstance().setPlayerStartingPositions();

    for(int i=0; i<map.territories().size(); i++){
        map.territories()[i]->addUnit(INFANTRY, STARTING_INFANTRY_NEUTRAL);
        TerritoryGraphicsItem *tg = new TerritoryGraphicsItem(map.territories()[i]);

        territories_.push_back(tg);
    }

    for(int i=0; i<map.connections().size(); i++){
        scene->addItem(map.connections()[i].get());
    }

    for(int i=0; i<territories_.size(); i++){
        scene->addItem(territories_[i]);
    }

    QColor c(Qt::blue);
    scene->setBackgroundBrush(QBrush(c.light(150), Qt::Dense2Pattern));

    setScene(scene);

    show();

    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);
}

void MapView::stop(){

}

void MapView::contextMenuEvent(QContextMenuEvent *event)
{
    resetSelected();
   
    selectedTerritory1_ = getTerritory(event->pos());

    if(!selectedTerritory1_)
        return;
    if(selectedTerritory1_->territory()->ownership() !=Player::getInstance().id())
        return;

    QMenu menu(this);
    menu.addAction(attackAction);
    menu.addAction(moveAction);
    menu.addAction(buyAction);
    menu.exec(event->globalPos());
}

void MapView::mouseMoveEvent(QMouseEvent *event){
    TerritoryGraphicsItem* selected = getTerritory(event->pos());
        if(selected){
            if(pointedTerritory_!=selected){
                if(pointedTerritory_)
                    pointedTerritory_->lightUp(false);
                pointedTerritory_ = selected;
                showTerritoryInfo(pointedTerritory_->territory()->id());
                pointedTerritory_->lightUp();
            }
        } else {
            if(pointedTerritory_){
                pointedTerritory_->lightUp(false);
                pointedTerritory_ = NULL;
                hideTerritoryInfo();
            }
        }
}

void MapView::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        TerritoryGraphicsItem* selected = getTerritory(event->pos());
        if(selected){
            if(selectedTerritory1_ && isSelectable(selected)){
                switch(selectedTerritory1_->state()){
                    case TerritoryGraphicsItem::ATTACKING:{
                        AttackDialog a(this, selectedTerritory1_->territory(),
                            selected->territory());
                        a.exec();
                                                          } break;
                    case TerritoryGraphicsItem::MOVING:{
                        MoveDialog a(this, selectedTerritory1_->territory(),
                            selected->territory());
                        a.exec();
                                                          } break;
                        break;
                }
                resetSelected();
            } else {
                //Logger::write(QString("Show info for ").append(selected->territory()->name()));
                //TODO display info
                //showTerritoryInfo(selected->territory()->id());
            }
        }
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void MapView::initActions(){
    attackAction = new QAction(tr("Attack"), this);
    connect(attackAction, SIGNAL(triggered()), this, SLOT(onAttack()));

    moveAction = new QAction(tr("Move"), this);
    connect(moveAction, SIGNAL(triggered()), this, SLOT(onMove()));

    buyAction = new QAction(tr("Buy"), this);
    connect(buyAction, SIGNAL(triggered()), this, SLOT(onBuy()));
}

void MapView::onAttack(){
    Logger::write("attack");
    selectedTerritory1_->attack();
    
    for(int i=0; i<territories_.size(); i++){
        TerritoryGraphicsItem* tgi = territories_[i];
        if(tgi->territory()->isNeighbour(selectedTerritory1_->territory()->id())
            && tgi->territory()->ownership() != selectedTerritory1_->territory()->ownership()){
            possibleSelections_.push_back(tgi);
            tgi->blink();
        }
    }
}

void MapView::onMove(){
    Logger::write("move");
    selectedTerritory1_->move();

    for(int i=0; i<territories_.size(); i++){
        TerritoryGraphicsItem* tgi = territories_[i];
        if(tgi->territory()->isNeighbour(selectedTerritory1_->territory()->id())
            && tgi->territory()->ownership() == selectedTerritory1_->territory()->ownership()){
            possibleSelections_.push_back(tgi);
            tgi->blink();
        }
    }

    /*MoveDialog a;
    a.exec();*/
}

void MapView::onBuy(){
    Logger::write("buy");
    BuyDialog a(this, selectedTerritory1_->territory());
    a.exec();
    updateStatusBar();
}

void MapView::resetSelected() {
    if(selectedTerritory1_){
        selectedTerritory1_->reset();
        selectedTerritory1_ = NULL;
    }
    for(int i=0; i<possibleSelections_.size(); i++){
        possibleSelections_[i]->reset();
    }
    possibleSelections_.clear();
}

TerritoryGraphicsItem* MapView::getTerritory(QPoint p){

    TerritoryGraphicsItem* found = NULL;
    foreach(QGraphicsItem* item, territories_){
        TerritoryGraphicsItem* tgi = dynamic_cast<TerritoryGraphicsItem*>(item);
        if(tgi)
            if(tgi->contains(p)){
                found = tgi;
                break;
            }
    }

   return found;
}

TerritoryGraphicsItem* MapView::getSelectableTerritory(QPoint p){
    if(possibleSelections_.empty())
        return NULL;

    TerritoryGraphicsItem* tgi = getTerritory(p);

    if(!tgi)
        return NULL;


    for(int i=0; i<possibleSelections_.size(); i++){
        if(tgi == possibleSelections_[i])
            return tgi;
    }

    return NULL;
}

bool MapView::isSelectable(TerritoryGraphicsItem* tgi){
    for(int i=0; i<possibleSelections_.size(); i++){
        if(tgi == possibleSelections_[i])
            return true;
    }
    return false;
}
