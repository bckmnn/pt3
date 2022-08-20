#include "logger.h"

#include <QApplication>
#include <QDate>
#include <QDir>
#include <QTextStream>

QString Logger::folderName = "logs";
QString Logger::fileName = "";

Logger::Logger(QObject *parent) : QObject(parent) {

}

bool Logger::init() {
    if(!QDir(Logger::folderName).exists()) {
        QDir().mkdir(Logger::folderName);
    }

    cleanUp();
    setFileName();

    QFile checkFile(Logger::fileName);

    if(checkFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qInstallMessageHandler(Logger::logMessageHandler);
        return true;
    }
    return false;
}

void Logger::setFileName() {
    Logger::fileName = QDir(Logger::folderName).filePath(
                           QString("%1_%2_pt3_log.txt")
                           .arg(QDate::currentDate().toString("yyyy-MM-dd"))
                           .arg(QTime::currentTime().toString("hh-mm-ss-zzz")));
}

void Logger::cleanUp() {
    QDir dir(QCoreApplication::applicationDirPath());
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time | QDir::Reversed);

    dir.setPath(Logger::folderName);

    QFileInfoList list = dir.entryInfoList();
    if (list.size() > MAXFILES) {
        for (int i = 0; i < (list.size() - MAXFILES); i++) {
            QString path = list.at(i).absoluteFilePath();
            QFile file(path);
            file.remove();
        }
    }
}

void Logger::logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &txt) {
    QFile checkFile(Logger::fileName);
    int size = checkFile.size();
    if (size > MAXSIZE) {
        cleanUp();
        setFileName();
    }

    QFile logFile(Logger::fileName);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&logFile);
    ts << "[" << type << "] " << context.file << ":" << context.line << " " << txt << endl;
}


