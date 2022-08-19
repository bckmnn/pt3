#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QObject>
#include <QQuickWidget>

class QmlWidget : public QQuickWidget
{
public:
    QmlWidget(QWidget *parent = nullptr);
};

#endif // QMLWIDGET_H
