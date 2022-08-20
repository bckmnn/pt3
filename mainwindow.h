#pragma once

#include <QMainWindow>
#include <QQuickWidget>
#include <QQuickWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addUpdateButton(QAction *action);

private slots:
    void on_quickWidget_sceneGraphError(const QQuickWindow::SceneGraphError &error, const QString &message);

    void on_quickWidget_statusChanged(const QQuickWidget::Status &arg1);

    void on_actionLoad_triggered();

    void on_actionshow_console_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

