#include <QTextBrowser>
#include <QString>

#ifndef LOGGER_H
#define LOGGER_H

/**
	Klasa pomocnicza do tworzenia logow
*/
class Logger {
public:
    Logger(QTextBrowser* logger);

    static void write(QString string);
private:
    static QTextBrowser* logger_;
};

#endif