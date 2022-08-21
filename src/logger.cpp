#include "logger.h"

#include <QApplication>
#include <QDate>
#include <QDir>
#include <QTextStream>

QString Logger::folderName = "logs";
QString Logger::fileName = "";

QStringList Logger::messages;
QStringListModel *Logger::messageModel;

#ifdef QT_DEBUG
bool Logger::logDebug = true;
#else
bool Logger::logDebug = false;
#endif


Logger::Logger(QObject *parent) : QObject(parent) {

}

bool Logger::init() {
    if(!QDir(Logger::folderName).exists()) {
        QDir().mkdir(Logger::folderName);
    }

    cleanUp();
    setFileName();

    messageModel = new QStringListModel();
    messageModel->setStringList(messages);

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
        for (int i = 0; i < (list.size() - (MAXFILES + 1)); i++) {
            QString path = list.at(i).absoluteFilePath();
            QFile file(path);
            file.remove();
        }
    }
}

void Logger::logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message) {
    QFile checkFile(Logger::fileName);
    int size = checkFile.size();
    if (size > MAXSIZE) {
        cleanUp();
        setFileName();
    }

    QFile logFile(Logger::fileName);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&logFile);

    QString msg;

    switch (type) {
    case QtDebugMsg:
        if(Logger::logDebug == false) {
            return;
        }
        msg.append("[debug] ");
        break;
    case QtInfoMsg:
        msg.append("[info ] ");
        break;
    case QtWarningMsg:
        msg.append("[warn ] ");
        break;
    case QtCriticalMsg:
        msg.append("[crit ] ");
        break;
    case QtFatalMsg:
        msg.append("[fatal] ");
        break;
    }

    msg.append("[");
    msg.append(context.category);
    msg.append("] ");
    msg.append(message);
    msg.append("\n");

    if(Logger::logDebug) {
        msg.append("        ");
        msg.append(context.file);
        msg.append(QString(":%1").arg(context.line));
    }

    ts << msg << endl;
    messages << msg;

    messageModel->setStringList(messages);
}


