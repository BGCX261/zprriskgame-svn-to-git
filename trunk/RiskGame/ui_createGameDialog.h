/********************************************************************************
** Form generated from reading UI file 'createGameDialog.ui'
**
** Created: Mon 7. Jun 21:28:23 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGAMEDIALOG_H
#define UI_CREATEGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateGameDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *titleLabel;
    QLabel *statusLabel;
    QLabel *infoLabel;
    QPushButton *createServerButton;

    void setupUi(QDialog *CreateGameDialog)
    {
        if (CreateGameDialog->objectName().isEmpty())
            CreateGameDialog->setObjectName(QString::fromUtf8("CreateGameDialog"));
        CreateGameDialog->resize(186, 164);
        buttonBox = new QDialogButtonBox(CreateGameDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 120, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        titleLabel = new QLabel(CreateGameDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(10, 10, 151, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        statusLabel = new QLabel(CreateGameDialog);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(10, 70, 141, 16));
        infoLabel = new QLabel(CreateGameDialog);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setGeometry(QRect(10, 40, 151, 21));
        createServerButton = new QPushButton(CreateGameDialog);
        createServerButton->setObjectName(QString::fromUtf8("createServerButton"));
        createServerButton->setGeometry(QRect(10, 90, 91, 23));

        retranslateUi(CreateGameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateGameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateGameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateGameDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateGameDialog)
    {
        CreateGameDialog->setWindowTitle(QApplication::translate("CreateGameDialog", "Create New Game", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("CreateGameDialog", "Create Game", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
        infoLabel->setText(QApplication::translate("CreateGameDialog", "Press button to create server", 0, QApplication::UnicodeUTF8));
        createServerButton->setText(QApplication::translate("CreateGameDialog", "Create server", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateGameDialog: public Ui_CreateGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGAMEDIALOG_H
