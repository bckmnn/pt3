#pragma once

#include <QObject>
#include <QQuickWidget>

class QmlWidget : public QQuickWidget
{
public:
    QmlWidget(QWidget *parent = nullptr);
};

