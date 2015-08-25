/********************************************************************************
** Form generated from reading UI file 'raportsDialog.ui'
**
** Created: Mon 7. Jun 21:28:23 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAPORTSDIALOG_H
#define UI_RAPORTSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_RaportDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *RaportDialog)
    {
        if (RaportDialog->objectName().isEmpty())
            RaportDialog->setObjectName(QString::fromUtf8("RaportDialog"));
        RaportDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(RaportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textBrowser = new QTextBrowser(RaportDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 381, 241));

        retranslateUi(RaportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RaportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RaportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RaportDialog);
    } // setupUi

    void retranslateUi(QDialog *RaportDialog)
    {
        RaportDialog->setWindowTitle(QApplication::translate("RaportDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RaportDialog: public Ui_RaportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAPORTSDIALOG_H
