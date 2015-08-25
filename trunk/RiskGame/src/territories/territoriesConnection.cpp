#include "territories/territoriesConnection.h"
#include "utils/logger.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QVector>

TerritoriesConnection::TerritoriesConnection(pTerritory t1, pTerritory t2)
{
    line_.moveTo(t1->getCenter());
    line_.lineTo(t2->getCenter());
}

TerritoriesConnection::TerritoriesConnection(QPoint p1, QPoint p2){
    line_.moveTo(p1);
    line_.lineTo(p2);
}

QRectF TerritoriesConnection::boundingRect() const
{
    return line_.boundingRect();
}

QPainterPath TerritoriesConnection::shape() const
{
    return line_;
}

void TerritoriesConnection::paint(QPainter *painter,
                const QStyleOptionGraphicsItem *, QWidget *){
    
    QPen pen;

    pen.setWidth(2);
    pen.setColor(Qt::black);


    painter->setPen(pen);
    painter->drawPath(line_);
}

QPainterPath TerritoriesConnection::line() const{
    return line_;
}
