#ifndef MYSTATUSBAR_H
#define MYSTATUSBAR_H

#include <QStatusBar>
#include <QLabel>

#include "player/player.h"

class MyStatusBar : public QStatusBar {
    Q_OBJECT
public:
    MyStatusBar ( QWidget * parent = 0);
    void update();
    void show(bool show = true){show_ = show;}
private:

    QLabel label1_;
    QLabel label2_;
    bool show_;
};

#endif