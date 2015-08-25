#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <QFile>
#include <QTextStream>
#include <QString>

/**
	Klasa pomocnicza do tworzenia logow
	@see Logger
*/
class FileLogger {
public:
	/**
		Kontruktor
	*/
    FileLogger()
        : file_("log.txt")
        , out_(&file_){
    file_.open(QIODevice::WriteOnly | QIODevice::Text);
    }
	/**
		@return	instancja klasy
	*/
    static FileLogger& instance(){
        static FileLogger l;
        return l;
    };
	/**
		sluzy do pisania do loga
		@param s napis ktory chcemy dodac
	*/
    static void write(QString s){

        instance().out()<<s<<endl;
        instance().out().flush();
    }
	/**
		@return wyjsciowy strumien
	*/
    QTextStream& out() {return out_;}

private:
    QFile file_;
    QTextStream out_;
};


#endif