
#include "utils/logger.h"

QTextBrowser* Logger::logger_ = NULL;


Logger::Logger(QTextBrowser* logger){
    if(!logger_)
        logger_ = logger;
}

void Logger::write(QString string) {
    if(logger_)
        logger_->setPlainText(logger_->toPlainText().append(string).append("\n"));
};

