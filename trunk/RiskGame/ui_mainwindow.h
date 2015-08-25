/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 7. Jun 21:28:23 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <mapview.h>
#include <mystatusbar.h>
#include <territories/territoryinfodisplay.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCreateGAme;
    QAction *actionJoinGame;
    QAction *actionZako_cz_ture;
    QAction *actionQuit;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    TerritoryInfoDisplay *territoryInfoLabel;
    QTextBrowser *logger;
    QPushButton *endTurnButton;
    MapView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    MyStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 456);
        actionCreateGAme = new QAction(MainWindow);
        actionCreateGAme->setObjectName(QString::fromUtf8("actionCreateGAme"));
        actionJoinGame = new QAction(MainWindow);
        actionJoinGame->setObjectName(QString::fromUtf8("actionJoinGame"));
        actionZako_cz_ture = new QAction(MainWindow);
        actionZako_cz_ture->setObjectName(QString::fromUtf8("actionZako_cz_ture"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 981, 402));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(horizontalLayoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(100, 200));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 169, 198));
        territoryInfoLabel = new TerritoryInfoDisplay(scrollAreaWidgetContents);
        territoryInfoLabel->setObjectName(QString::fromUtf8("territoryInfoLabel"));
        territoryInfoLabel->setGeometry(QRect(0, 0, 171, 201));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        logger = new QTextBrowser(horizontalLayoutWidget);
        logger->setObjectName(QString::fromUtf8("logger"));

        verticalLayout->addWidget(logger);

        endTurnButton = new QPushButton(horizontalLayoutWidget);
        endTurnButton->setObjectName(QString::fromUtf8("endTurnButton"));

        verticalLayout->addWidget(endTurnButton);


        horizontalLayout->addLayout(verticalLayout);

        graphicsView = new MapView(horizontalLayoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(800, 400));

        horizontalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 20));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new MyStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionCreateGAme);
        menuMenu->addAction(actionJoinGame);
        menuMenu->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RiskGame", 0, QApplication::UnicodeUTF8));
        actionCreateGAme->setText(QApplication::translate("MainWindow", "Create New Game", 0, QApplication::UnicodeUTF8));
        actionJoinGame->setText(QApplication::translate("MainWindow", "Join Existing Game", 0, QApplication::UnicodeUTF8));
        actionZako_cz_ture->setText(QApplication::translate("MainWindow", "Zako\305\204cz ture", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        territoryInfoLabel->setText(QString());
        endTurnButton->setText(QApplication::translate("MainWindow", "Zako\305\204cz tur\304\231", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
