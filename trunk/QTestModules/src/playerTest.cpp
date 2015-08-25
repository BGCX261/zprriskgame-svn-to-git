#include "playertest.h"

void PlayerTest::initTestCase(){
    p = &Player::getInstance();
    
}
void PlayerTest::cleanupTestCase(){
    p->clearCommands();
}
void PlayerTest::init(){
    p->clearCommands();
}
void PlayerTest::cleanup(){
}

void PlayerTest::addCommand(){
    QCOMPARE(p->commands().size(), 0);

    p->addCommand(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));

    QCOMPARE(p->commands().size(), 1);

    p->addCommand(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));
    p->addCommand(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));
    p->addCommand(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));

    QCOMPARE(p->commands().size(), 4);
}

void PlayerTest::addCommands(){
    QCOMPARE(p->commands().size(), 0);

    commandVect v;
    v.push_back(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));
    v.push_back(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));
    v.push_back(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));
    v.push_back(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));

    QCOMPARE(v.size(), 4);

    p->addCommands(v);

    QCOMPARE(p->commands().size(), 4);
}


void PlayerTest::sendCommand(){
    QCOMPARE(p->commands().size(), 0);
    p->addCommand(CommandsFactory::getInstance().create(ATTACK_COMMAND, 1,2,3,4));

    commandVect v = p->getCommandsAndReset();

    QCOMPARE(v.size(),1);
    QCOMPARE(p->commands().size(), 0);

}

void PlayerTest::money(){
    QCOMPARE(p->money(), MONEY_STARTING);

    p->addMoney(100);
    QCOMPARE(p->money(), MONEY_STARTING + 100);

    p->addMoney(-100);
    QCOMPARE(p->money(), MONEY_STARTING);

    p->setMoney(500);
    QCOMPARE(p->money(), 500);

}

void PlayerTest::id(){
    QCOMPARE(p->id(), NEUTRAL);

    p->setId(PLAYER1);
    QCOMPARE(p->id(), PLAYER1);

    p->setId(PLAYER2);
    QCOMPARE(p->id(), PLAYER2);
}