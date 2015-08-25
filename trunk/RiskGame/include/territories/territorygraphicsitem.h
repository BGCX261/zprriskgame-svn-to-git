#ifndef TERRITORYGRAPHICSITEM_H
#define TERRITORYGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QColor>

#include "territories/territory.h"
#include "utils/constants.h"

#include <boost/shared_ptr.hpp>

class TerritoryGraphicsItem : public QGraphicsItem
{
public:

    enum State {
        NONE,
        ATTACKING,
        MOVING,
        RESETING
    };

    TerritoryGraphicsItem(pTerritory territory);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    bool contains(QPoint point);


    void attack();
    void move();
    void reset();

    void blink(bool on = true);
    void lightUp(bool on=true);
    bool isBlinking() const {return blinking_;}


    pTerritory territory() {return territory_;}
    State state() {return state_;}
protected:
    void advance(int step);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:

    pTerritory territory_;
    QPainterPath border_;
    State state_;

    int blinkValue_;
    bool blinking_;

    bool lightUp_;
};

#endif // TERRITORYGRAPHICSITEM_H
