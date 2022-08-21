#pragma once

#include <QObject>
#include <QStringListModel>

#define MAXFILES 3
#define MAXSIZE 1024 * 100

class Logger : public QObject {
    Q_OBJECT
  public:
    explicit Logger(QObject *parent = nullptr);

    static bool init();
    static void setFileName();
    static void cleanUp();
    static void clearMessages();

    static QString folderName;
    static QString fileName;

    static bool logDebug;

    static QStringList messages;
    static QStringListModel *messageModel;

    static void logMessageHandler(QtMsgType type, const QMessageLogContext &context,
                                  const QString& txt);

  signals:

};

