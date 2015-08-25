/********************************************************************************
** Form generated from reading UI file 'movingDialog.ui'
**
** Created: Sun 30. May 15:38:55 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVINGDIALOG_H
#define UI_MOVINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MoveDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *titleLabel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *moveRightButton;
    QPushButton *moveLeftButton;
    QPushButton *moveAllRightButton;
    QPushButton *moveAllLeftButton;
    QTableWidget *leftTable;
    QTableWidget *rightTable;
    QLabel *label_3;
    QPushButton *backToStartButton;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *distanceLabel;
    QLabel *unitsLabel;
    QLabel *costLabel;
    QLabel *moneyLabel;

    void setupUi(QDialog *MoveDialog)
    {
        if (MoveDialog->objectName().isEmpty())
            MoveDialog->setObjectName(QString::fromUtf8("MoveDialog"));
        MoveDialog->resize(282, 327);
        buttonBox = new QDialogButtonBox(MoveDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-60, 290, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        titleLabel = new QLabel(MoveDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(10, 10, 381, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        label = new QLabel(MoveDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 50, 81, 16));
        label_2 = new QLabel(MoveDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 50, 81, 16));
        moveRightButton = new QPushButton(MoveDialog);
        moveRightButton->setObjectName(QString::fromUtf8("moveRightButton"));
        moveRightButton->setGeometry(QRect(10, 230, 81, 23));
        moveLeftButton = new QPushButton(MoveDialog);
        moveLeftButton->setObjectName(QString::fromUtf8("moveLeftButton"));
        moveLeftButton->setGeometry(QRect(100, 230, 81, 23));
        moveAllRightButton = new QPushButton(MoveDialog);
        moveAllRightButton->setObjectName(QString::fromUtf8("moveAllRightButton"));
        moveAllRightButton->setGeometry(QRect(10, 260, 81, 23));
        moveAllLeftButton = new QPushButton(MoveDialog);
        moveAllLeftButton->setObjectName(QString::fromUtf8("moveAllLeftButton"));
        moveAllLeftButton->setGeometry(QRect(100, 260, 81, 23));
        leftTable = new QTableWidget(MoveDialog);
        leftTable->setObjectName(QString::fromUtf8("leftTable"));
        leftTable->setGeometry(QRect(10, 70, 81, 151));
        rightTable = new QTableWidget(MoveDialog);
        rightTable->setObjectName(QString::fromUtf8("rightTable"));
        rightTable->setGeometry(QRect(100, 70, 81, 151));
        label_3 = new QLabel(MoveDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(190, 70, 61, 16));
        backToStartButton = new QPushButton(MoveDialog);
        backToStartButton->setObjectName(QString::fromUtf8("backToStartButton"));
        backToStartButton->setGeometry(QRect(10, 290, 81, 23));
        label_4 = new QLabel(MoveDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 110, 71, 16));
        label_5 = new QLabel(MoveDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(190, 150, 61, 16));
        label_6 = new QLabel(MoveDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(190, 190, 61, 16));
        distanceLabel = new QLabel(MoveDialog);
        distanceLabel->setObjectName(QString::fromUtf8("distanceLabel"));
        distanceLabel->setGeometry(QRect(190, 90, 46, 13));
        unitsLabel = new QLabel(MoveDialog);
        unitsLabel->setObjectName(QString::fromUtf8("unitsLabel"));
        unitsLabel->setGeometry(QRect(190, 130, 46, 13));
        costLabel = new QLabel(MoveDialog);
        costLabel->setObjectName(QString::fromUtf8("costLabel"));
        costLabel->setGeometry(QRect(190, 170, 46, 13));
        moneyLabel = new QLabel(MoveDialog);
        moneyLabel->setObjectName(QString::fromUtf8("moneyLabel"));
        moneyLabel->setGeometry(QRect(190, 210, 46, 13));

        retranslateUi(MoveDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MoveDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MoveDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MoveDialog);
    } // setupUi

    void retranslateUi(QDialog *MoveDialog)
    {
        MoveDialog->setWindowTitle(QApplication::translate("MoveDialog", "Move", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("MoveDialog", "You're moving between A and B", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MoveDialog", "Forces", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MoveDialog", "Forces", 0, QApplication::UnicodeUTF8));
        moveRightButton->setText(QApplication::translate("MoveDialog", "Move Right", 0, QApplication::UnicodeUTF8));
        moveLeftButton->setText(QApplication::translate("MoveDialog", "Move Left", 0, QApplication::UnicodeUTF8));
        moveAllRightButton->setText(QApplication::translate("MoveDialog", "Move All Right", 0, QApplication::UnicodeUTF8));
        moveAllLeftButton->setText(QApplication::translate("MoveDialog", "Move All Left", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MoveDialog", "Distance:", 0, QApplication::UnicodeUTF8));
        backToStartButton->setText(QApplication::translate("MoveDialog", "Back to Start", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MoveDialog", "Moving units:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MoveDialog", "Moving cost", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MoveDialog", "Money left:", 0, QApplication::UnicodeUTF8));
        distanceLabel->setText(QApplication::translate("MoveDialog", "0", 0, QApplication::UnicodeUTF8));
        unitsLabel->setText(QApplication::translate("MoveDialog", "0", 0, QApplication::UnicodeUTF8));
        costLabel->setText(QApplication::translate("MoveDialog", "0", 0, QApplication::UnicodeUTF8));
        moneyLabel->setText(QApplication::translate("MoveDialog", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MoveDialog: public Ui_MoveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVINGDIALOG_H
