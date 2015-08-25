#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "utils/defs.h"
#include "utils/logger.h"
#include "utils/singleton.h"

#include "map.h"

#include "dialogs/createGameDialog.h"
#include "dialogs/joinGameDialog.h"
#include "dialogs/raportDialog.h"

#include "player/player.h"

#include "commands/commandsfactory.h"
#include "units/unitsfactory.h"
#include "raports/raportfactory.h"
#include "buildings/buildingsfactory.h"


#include "utils/ids.h"

#include "calculator/calculator.h"
#include "calculator/interpreter.h"

#include <fstream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void endGame(EndGameId id);

protected:
    void changeEvent(QEvent *e);
    
private slots:
    void startNewGame();
    void connectToGame();
    void quit();
    void endTurn();
    void showTerritoryInfo(int id);
    void hideTerritoryInfo();
    void updateStatusBar();
private:
    void checkVictory();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
