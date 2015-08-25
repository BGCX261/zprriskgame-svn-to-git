#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QTimer>
#include <QPoint>
#include <QVector>

#include <QVector>

#include "territories/territorygraphicsitem.h"
#include "territories/territory.h"
#include "territories/territoriesConnection.h"
#include "utils/logger.h"
#include "utils/defs.h"
#include "dialogs/attackDialog.h"
#include "dialogs/moveDialog.h"
#include "dialogs/buyDialog.h"
#include "map.h"

#include <boost/shared_ptr.hpp>

class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    typedef QVector<TerritoryGraphicsItem*> tgiVect;
    MapView(QWidget* widget);

protected:
     void contextMenuEvent(QContextMenuEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);

signals:
    void showTerritoryInfo(int id);
    void hideTerritoryInfo();
    void updateStatusBar();

public slots:
    void start();
    void stop();

private slots:
    void onAttack();
    void onMove();
    void onBuy();

private:
    void initActions();

    void resetSelected();

    TerritoryGraphicsItem* getTerritory(QPoint p);
    TerritoryGraphicsItem* getSelectableTerritory(QPoint p);

    bool isSelectable(TerritoryGraphicsItem* tgi);

    TerritoryGraphicsItem* selectedTerritory1_;
    TerritoryGraphicsItem* pointedTerritory_;
    tgiVect territories_;
    tgiVect possibleSelections_;


    QAction* attackAction;
    QAction* moveAction;
    QAction* buyAction;
};

#endif // MAPVIEW_H
