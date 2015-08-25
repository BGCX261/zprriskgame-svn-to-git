#ifndef TerritoriesConnection_H
#define TerritoriesConnection_H

#include <QGraphicsItem>
#include <QColor>
#include <QPoint>

#include "territories/territory.h"

#include <boost/shared_ptr.hpp>

class Territory;
/**
	Klasa okresla polaczenia miedzy terytoriami, ktore sa oddzielone morzem.
*/
class TerritoriesConnection : public QGraphicsItem
{
public:
	/**
		Kontruktor
		@param t1 terytorium pierwsze
		@param t2 terytorium drugie
	*/
    TerritoriesConnection(pTerritory t1, pTerritory t2);
	/**
		Konstruktor dla linii z punktami rysowania podanymi wprost
		@param p1 punkt od ktorego ma byc rysowana linia
		@param p2 punkt do ktorego ma byc rysowana linia
	*/
    TerritoriesConnection(QPoint p1, QPoint p2);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    QPainterPath line() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

protected:

private:
    QPainterPath line_;
};

#endif // TerritoriesConnection_H
