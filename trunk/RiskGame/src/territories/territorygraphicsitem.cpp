#include "territories/territorygraphicsitem.h"
#include "utils/logger.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QVector>

#include "boost/shared_ptr.hpp"

TerritoryGraphicsItem::TerritoryGraphicsItem(pTerritory territory)
    : territory_(territory)
    , state_(NONE)
    , blinkValue_(BRUSH_LIGHT_NORMAL)
    , blinking_(false)
    , lightUp_(false)
{
    border_.moveTo(territory->getPoints()[0]);
    for(int i=1; i<territory->getPoints().size(); i++){
        border_.lineTo(territory->getPoints()[i]);
    }

    border_.closeSubpath();
}

QRectF TerritoryGraphicsItem::boundingRect() const
{
    return border_.boundingRect();
}

QPainterPath TerritoryGraphicsItem::shape() const
{
    return border_;
}

void TerritoryGraphicsItem::paint(QPainter *painter,
                const QStyleOptionGraphicsItem *, QWidget *){
    
    QPen pen;
    QBrush brush;

    QColor color(Qt::black);
    int width = 1;

    switch(state_){
        case ATTACKING: 
            color = QColor(Qt::red); 
            width = 3;
            break;
        case MOVING: 
            color = QColor(Qt::blue);
            width = 3;
            break;
    };

    pen.setWidth(width);
    pen.setColor(color);

    int light;
    if(lightUp_)
        light = BRUSH_LIGHT_MAX;
    else if(blinking_)
        light = blinkValue_;
    else 
        light = BRUSH_LIGHT_NORMAL;

    QLinearGradient linearGradient(border_.boundingRect().topLeft(), border_.boundingRect().bottomRight());
    linearGradient.setColorAt(0.0, Qt::white);
    linearGradient.setColorAt(0.8, PLAYER_COLORS[territory_->ownership()].light(light));
    linearGradient.setColorAt(1.0, Qt::black);
    brush = QBrush(linearGradient);

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(border_);

    if(territory_->isVisible()){
        if(territory_->hasBuilding(BUNKER)){
            painter->setBrush(QBrush(Qt::DiagCrossPattern));
            painter->drawPath(border_);
        }

        
        painter->setFont(QFont("Times", 8, QFont::Bold));

        painter->drawText(QRect(territory_->getCenter() - QPoint(5,5),
            territory_->getCenter() + QPoint(5,5)), Qt::AlignCenter, QString::number(
            territory_->noUnits()));
    }
}

void TerritoryGraphicsItem::advance(int step){
    if(!step)
        return;
    bool change = false;

    if(blinking_){
        blinkValue_ += 5;
            if(blinkValue_ > BRUSH_LIGHT_MAX)
                blinkValue_ = BRUSH_LIGHT_MIN;
        change = true;
    }

    if(state_ == RESETING){
        state_ = NONE;
        change = true;
    }

    if(change)
        update();
}

QVariant TerritoryGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
 {
     switch (change) {
     case ItemPositionHasChanged:
         
         break;
     default:
         break;
     };

     return QGraphicsItem::itemChange(change, value);
 }

 /*void TerritoryGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
     territory_.setSelected(!territory_.isSelected());
     update();
     QGraphicsItem::mousePressEvent(event);
 }

 void TerritoryGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
 {
     update();
     QGraphicsItem::mouseReleaseEvent(event);
 }*/

 bool TerritoryGraphicsItem::contains(QPoint point){
     return border_.contains(point);
 }

 void TerritoryGraphicsItem::attack(){
     state_ = ATTACKING;
 }

 void TerritoryGraphicsItem::move(){
     state_ = MOVING;
 }

 void TerritoryGraphicsItem::blink(bool on){
     blinking_ = on;
 }

 void TerritoryGraphicsItem::lightUp(bool on){
     lightUp_ = on;
     update();
 }

 void TerritoryGraphicsItem::reset(){
     state_ = RESETING;
     blinking_ = false;
     lightUp_ = false;
 }
