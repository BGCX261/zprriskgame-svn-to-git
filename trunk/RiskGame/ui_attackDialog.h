/********************************************************************************
** Form generated from reading UI file 'attackDialog.ui'
**
** Created: Mon 7. Jun 21:28:24 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTACKDIALOG_H
#define UI_ATTACKDIALOG_H

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

class Ui_AttackDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *titleLabel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *addAllButton;
    QPushButton *removeAllButton;
    QLabel *infoTitleLabel;
    QTableWidget *availableTable;
    QTableWidget *chosenTable;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *watchtowerLabel;
    QLabel *noUnitsLabel;
    QLabel *bunkerLabel;

    void setupUi(QDialog *AttackDialog)
    {
        if (AttackDialog->objectName().isEmpty())
            AttackDialog->setObjectName(QString::fromUtf8("AttackDialog"));
        AttackDialog->resize(410, 300);
        buttonBox = new QDialogButtonBox(AttackDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        titleLabel = new QLabel(AttackDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(10, 10, 381, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        label = new QLabel(AttackDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 50, 81, 16));
        label_2 = new QLabel(AttackDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 50, 81, 16));
        addButton = new QPushButton(AttackDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(10, 230, 81, 23));
        removeButton = new QPushButton(AttackDialog);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(100, 230, 81, 23));
        addAllButton = new QPushButton(AttackDialog);
        addAllButton->setObjectName(QString::fromUtf8("addAllButton"));
        addAllButton->setGeometry(QRect(10, 260, 81, 23));
        removeAllButton = new QPushButton(AttackDialog);
        removeAllButton->setObjectName(QString::fromUtf8("removeAllButton"));
        removeAllButton->setGeometry(QRect(100, 260, 81, 23));
        infoTitleLabel = new QLabel(AttackDialog);
        infoTitleLabel->setObjectName(QString::fromUtf8("infoTitleLabel"));
        infoTitleLabel->setGeometry(QRect(220, 50, 171, 16));
        availableTable = new QTableWidget(AttackDialog);
        availableTable->setObjectName(QString::fromUtf8("availableTable"));
        availableTable->setGeometry(QRect(10, 70, 81, 151));
        chosenTable = new QTableWidget(AttackDialog);
        chosenTable->setObjectName(QString::fromUtf8("chosenTable"));
        chosenTable->setGeometry(QRect(100, 70, 81, 151));
        label_3 = new QLabel(AttackDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(220, 70, 91, 16));
        label_4 = new QLabel(AttackDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 90, 91, 16));
        label_5 = new QLabel(AttackDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(220, 110, 91, 16));
        watchtowerLabel = new QLabel(AttackDialog);
        watchtowerLabel->setObjectName(QString::fromUtf8("watchtowerLabel"));
        watchtowerLabel->setGeometry(QRect(320, 110, 61, 16));
        noUnitsLabel = new QLabel(AttackDialog);
        noUnitsLabel->setObjectName(QString::fromUtf8("noUnitsLabel"));
        noUnitsLabel->setGeometry(QRect(320, 70, 61, 16));
        bunkerLabel = new QLabel(AttackDialog);
        bunkerLabel->setObjectName(QString::fromUtf8("bunkerLabel"));
        bunkerLabel->setGeometry(QRect(320, 90, 61, 16));

        retranslateUi(AttackDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AttackDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AttackDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AttackDialog);
    } // setupUi

    void retranslateUi(QDialog *AttackDialog)
    {
        AttackDialog->setWindowTitle(QApplication::translate("AttackDialog", "Attack", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("AttackDialog", "You're attacking A from B", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AttackDialog", "Available forces", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AttackDialog", "Chosen forces", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("AttackDialog", "Add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("AttackDialog", "Remove", 0, QApplication::UnicodeUTF8));
        addAllButton->setText(QApplication::translate("AttackDialog", "Add All", 0, QApplication::UnicodeUTF8));
        removeAllButton->setText(QApplication::translate("AttackDialog", "Remove All", 0, QApplication::UnicodeUTF8));
        infoTitleLabel->setText(QApplication::translate("AttackDialog", "Information about enemy territory:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AttackDialog", "Number of units:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AttackDialog", "Bunker:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AttackDialog", "Watchtower:", 0, QApplication::UnicodeUTF8));
        watchtowerLabel->setText(QApplication::translate("AttackDialog", "Unknown", 0, QApplication::UnicodeUTF8));
        noUnitsLabel->setText(QApplication::translate("AttackDialog", "Unknown", 0, QApplication::UnicodeUTF8));
        bunkerLabel->setText(QApplication::translate("AttackDialog", "Unknown", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AttackDialog: public Ui_AttackDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTACKDIALOG_H
