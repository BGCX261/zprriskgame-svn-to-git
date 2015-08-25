/********************************************************************************
** Form generated from reading UI file 'joinGameDialog.ui'
**
** Created: Mon 7. Jun 21:28:23 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINGAMEDIALOG_H
#define UI_JOINGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_JoinGameDialog
{
public:
    QLabel *titleLabel;
    QLabel *label;
    QLineEdit *addressLine;
    QLabel *label_2;
    QLineEdit *portLine;
    QPushButton *joinButton;
    QLabel *statusLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *JoinGameDialog)
    {
        if (JoinGameDialog->objectName().isEmpty())
            JoinGameDialog->setObjectName(QString::fromUtf8("JoinGameDialog"));
        JoinGameDialog->resize(183, 170);
        titleLabel = new QLabel(JoinGameDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(30, 10, 111, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        label = new QLabel(JoinGameDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 41, 16));
        addressLine = new QLineEdit(JoinGameDialog);
        addressLine->setObjectName(QString::fromUtf8("addressLine"));
        addressLine->setGeometry(QRect(60, 40, 101, 20));
        label_2 = new QLabel(JoinGameDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 41, 16));
        portLine = new QLineEdit(JoinGameDialog);
        portLine->setObjectName(QString::fromUtf8("portLine"));
        portLine->setGeometry(QRect(60, 70, 101, 20));
        joinButton = new QPushButton(JoinGameDialog);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        joinButton->setGeometry(QRect(10, 100, 75, 23));
        statusLabel = new QLabel(JoinGameDialog);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(90, 100, 71, 21));
        buttonBox = new QDialogButtonBox(JoinGameDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 130, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        retranslateUi(JoinGameDialog);

        QMetaObject::connectSlotsByName(JoinGameDialog);
    } // setupUi

    void retranslateUi(QDialog *JoinGameDialog)
    {
        JoinGameDialog->setWindowTitle(QApplication::translate("JoinGameDialog", "Join Game", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("JoinGameDialog", "Join Game", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("JoinGameDialog", "Address:", 0, QApplication::UnicodeUTF8));
        addressLine->setText(QApplication::translate("JoinGameDialog", "123.123.123.123", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("JoinGameDialog", "Port:", 0, QApplication::UnicodeUTF8));
        portLine->setText(QApplication::translate("JoinGameDialog", "12345", 0, QApplication::UnicodeUTF8));
        joinButton->setText(QApplication::translate("JoinGameDialog", "Join", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QApplication::translate("JoinGameDialog", "....", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class JoinGameDialog: public Ui_JoinGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINGAMEDIALOG_H
