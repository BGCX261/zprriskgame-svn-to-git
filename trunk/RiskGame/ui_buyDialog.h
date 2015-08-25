/********************************************************************************
** Form generated from reading UI file 'buyDialog.ui'
**
** Created: Mon 7. Jun 21:28:24 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYDIALOG_H
#define UI_BUYDIALOG_H

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

class Ui_BuyDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *titleLabel;
    QLabel *label_2;
    QLabel *moneyLabel;
    QLabel *label_3;
    QTableWidget *buyTable;
    QTableWidget *chosenTable;
    QTableWidget *territoryTable;
    QLabel *costLabel;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *buyButton;
    QPushButton *clearButton;
    QLabel *label;
    QTableWidget *territoryTable2;
    QLabel *label_7;
    QLabel *label_8;
    QTableWidget *chosenTable2;
    QLabel *label_9;
    QTableWidget *buyTable2;
    QLabel *label_10;

    void setupUi(QDialog *BuyDialog)
    {
        if (BuyDialog->objectName().isEmpty())
            BuyDialog->setObjectName(QString::fromUtf8("BuyDialog"));
        BuyDialog->resize(372, 512);
        buttonBox = new QDialogButtonBox(BuyDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 470, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        titleLabel = new QLabel(BuyDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(10, 10, 201, 16));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        label_2 = new QLabel(BuyDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 10, 71, 16));
        label_2->setFont(font);
        moneyLabel = new QLabel(BuyDialog);
        moneyLabel->setObjectName(QString::fromUtf8("moneyLabel"));
        moneyLabel->setGeometry(QRect(290, 10, 51, 16));
        moneyLabel->setFont(font);
        label_3 = new QLabel(BuyDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 80, 46, 13));
        buyTable = new QTableWidget(BuyDialog);
        buyTable->setObjectName(QString::fromUtf8("buyTable"));
        buyTable->setGeometry(QRect(10, 100, 111, 141));
        chosenTable = new QTableWidget(BuyDialog);
        chosenTable->setObjectName(QString::fromUtf8("chosenTable"));
        chosenTable->setGeometry(QRect(130, 100, 111, 141));
        territoryTable = new QTableWidget(BuyDialog);
        territoryTable->setObjectName(QString::fromUtf8("territoryTable"));
        territoryTable->setGeometry(QRect(250, 100, 111, 141));
        costLabel = new QLabel(BuyDialog);
        costLabel->setObjectName(QString::fromUtf8("costLabel"));
        costLabel->setGeometry(QRect(290, 30, 51, 16));
        costLabel->setFont(font);
        label_4 = new QLabel(BuyDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 30, 71, 16));
        label_4->setFont(font);
        label_5 = new QLabel(BuyDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(130, 80, 46, 13));
        label_6 = new QLabel(BuyDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(250, 80, 61, 16));
        addButton = new QPushButton(BuyDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(10, 390, 111, 23));
        removeButton = new QPushButton(BuyDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(130, 390, 111, 23));
        buyButton = new QPushButton(BuyDialog);
        buyButton->setObjectName(QString::fromUtf8("buyButton"));
        buyButton->setGeometry(QRect(130, 422, 231, 41));
        clearButton = new QPushButton(BuyDialog);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(10, 420, 111, 23));
        label = new QLabel(BuyDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 46, 13));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        territoryTable2 = new QTableWidget(BuyDialog);
        territoryTable2->setObjectName(QString::fromUtf8("territoryTable2"));
        territoryTable2->setGeometry(QRect(250, 290, 111, 91));
        label_7 = new QLabel(BuyDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 250, 111, 16));
        label_7->setFont(font1);
        label_8 = new QLabel(BuyDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 270, 46, 13));
        chosenTable2 = new QTableWidget(BuyDialog);
        chosenTable2->setObjectName(QString::fromUtf8("chosenTable2"));
        chosenTable2->setGeometry(QRect(130, 290, 111, 91));
        label_9 = new QLabel(BuyDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(130, 270, 46, 13));
        buyTable2 = new QTableWidget(BuyDialog);
        buyTable2->setObjectName(QString::fromUtf8("buyTable2"));
        buyTable2->setGeometry(QRect(10, 290, 111, 91));
        label_10 = new QLabel(BuyDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(250, 270, 61, 16));

        retranslateUi(BuyDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BuyDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BuyDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BuyDialog);
    } // setupUi

    void retranslateUi(QDialog *BuyDialog)
    {
        BuyDialog->setWindowTitle(QApplication::translate("BuyDialog", "Buy", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("BuyDialog", "Buying for A", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BuyDialog", "Money:", 0, QApplication::UnicodeUTF8));
        moneyLabel->setText(QApplication::translate("BuyDialog", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BuyDialog", "To Buy:", 0, QApplication::UnicodeUTF8));
        costLabel->setText(QApplication::translate("BuyDialog", "0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BuyDialog", "Cost:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BuyDialog", "Chosen:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("BuyDialog", "In territory:", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("BuyDialog", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("BuyDialog", "Remove", 0, QApplication::UnicodeUTF8));
        buyButton->setText(QApplication::translate("BuyDialog", "Buy", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("BuyDialog", "Clear Buy List", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BuyDialog", "Units:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("BuyDialog", "Buildings:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("BuyDialog", "To Buy:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("BuyDialog", "Chosen:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("BuyDialog", "In territory:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BuyDialog: public Ui_BuyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYDIALOG_H
