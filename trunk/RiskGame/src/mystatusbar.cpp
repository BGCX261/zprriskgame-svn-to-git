
#include "mystatusbar.h"

#include "utils/singleton.h"


MyStatusBar::MyStatusBar( QWidget * parent)
: QStatusBar(parent)
, label1_(this)
, label2_(this)
, show_(false){
    addPermanentWidget(&label1_);
    addPermanentWidget(&label2_);

    update();
}

void MyStatusBar::update(){
    if(show_){
        label1_.setText(QString("Money: ")
            .append(QString::number(Player::getInstance().money())));
        label2_.setText(QString("Player ")
            .append(Player::getInstance().name()));
    }
}