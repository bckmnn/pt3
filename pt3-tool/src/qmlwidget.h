#pragma once

#include <QObject>
#include <QQuickWidget>
#include <QLoggingCategory>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(log_qmlwidget);


class QmlWidget : public QQuickWidget {
    Q_OBJECT
  public:
    QmlWidget(QWidget *parent = nullptr);

  signals:
    void availableTranslationsChanged();

  protected:

    void clearComponentCache();
    bool checkDragMimeData(const QMimeData *mimedata);

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void loadQmlFile(const QUrl url);

    void setupImportPaths();
    void setupTranslations();

  private:
    QString m_protoPath;
    QString m_protoFile;
    QStringList m_availableTranslations;

};

