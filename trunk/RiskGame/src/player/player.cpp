#include "player/player.h"


Player::Player(QString name, bool server, int money)
: name_(name)
, money_(money)
, isServer_(server)
, commands_()
, id_(NEUTRAL){

}

void Player::addCommand(pCommand c) {
    Logger::write("Added 1 command");
    commands_.push_back(c);
}

void Player::addCommands(commandVect v) { 
    Logger::write(QString("Added ").append(QString::number(v.size())).append(" commands"));
    commands_+=v;
}