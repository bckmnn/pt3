#include "qmlwidget.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMimeData>
#include <QOperatingSystemVersion>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

Q_LOGGING_CATEGORY(log_qmlwidget, "pt3.qmlwidget");

QmlWidget::QmlWidget(QWidget *parent):
    QQuickWidget(parent) {
    setResizeMode(QQuickWidget::SizeRootObjectToView);

    bool is_mac = QOperatingSystemVersion::current().type() == QOperatingSystemVersion::MacOS;

    QString app_working_dir(QDir::cleanPath(QDir(".").absolutePath()));
    QString app_dir((is_mac) ? QDir::cleanPath(QCoreApplication::applicationDirPath()+"/../../..")
                    : QCoreApplication::applicationDirPath());
    QString bundle_dir((is_mac) ? QDir::cleanPath(QCoreApplication::applicationDirPath()+"/../..")
                       : QCoreApplication::applicationDirPath());

    engine()->addImportPath(QDir(app_dir).filePath("imports"));
}

void QmlWidget::clearComponentCache() {
    engine()->trimComponentCache();
    engine()->clearComponentCache();
}

bool QmlWidget::checkDragMimeData(const QMimeData *mimedata) {
    if(mimedata->hasUrls()) {
        QUrl url = mimedata->urls().at(0);
        if(url.path().endsWith(".proto") || url.path().endsWith(".proto/") ) {
            return true;
        }
    }
    return false;
}


void QmlWidget::dragEnterEvent(QDragEnterEvent *event) {
    if(checkDragMimeData(event->mimeData())) {
        event->accept();
    }
}

void QmlWidget::dropEvent(QDropEvent *event) {
    if(checkDragMimeData(event->mimeData())) {
        event->accept();
        QUrl url = event->mimeData()->urls()[0];
        QString path = url.path();
        if(path.endsWith("/")) {
            url.setPath(path.append("main.qml"));
        } else {
            url.setPath(path.append("/main.qml"));
        }
        qDebug(log_qmlwidget) << "url: " << url;
        loadQmlFile(url);
    }
}

void QmlWidget::loadQmlFile(const QUrl url) {
    QFileInfo qmlFileInfo(url.toString());
    if(url.isLocalFile()) {
        qmlFileInfo = QFileInfo(url.toLocalFile());
    }

    m_protoPath = qmlFileInfo.path();
    m_protoFile = qmlFileInfo.fileName();

    setupTranslations();
    setupImportPaths();

    qDebug(log_qmlwidget) << "loading: " << QDir(m_protoPath).filePath(m_protoFile);
    setSource(QUrl());
    clearComponentCache();
    setSource(url);

}

void QmlWidget::setupImportPaths() {
    QDir importsFolder(m_protoPath);
    if(importsFolder.cd("imports")) {
        engine()->addImportPath(importsFolder.absolutePath());
        qInfo(log_qmlwidget) << "added ./imports folder " << importsFolder;
    } else {
        qInfo(log_qmlwidget) << "no ./imports folder found in " << importsFolder;
    }

    qDebug(log_qmlwidget) << "current qml import paths:";
    for(const auto &p : engine()->importPathList()) {
        qDebug(log_qmlwidget) << p;
    }
}

void QmlWidget::setupTranslations() {
    QDir translationsFolder(m_protoPath);
    if(translationsFolder.cd("translation")) {
        QStringList filters = {"*.qm"};
        translationsFolder.setNameFilters(filters);
        qInfo(log_qmlwidget) << "loading translations from " << translationsFolder;
        m_availableTranslations.clear();
        for(auto f : translationsFolder.entryList() ) {
            m_availableTranslations << f.replace("lang_","").replace(".qm","");
        }
        emit availableTranslationsChanged();
    } else {
        qInfo(log_qmlwidget) << "no ./translation folder found in " << translationsFolder;
    }

}


void QmlWidget::dragMoveEvent(QDragMoveEvent *event) {
    if(checkDragMimeData(event->mimeData())) {
        event->accept();
    }
}
