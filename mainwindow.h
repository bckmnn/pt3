#pragma once

#include <QMainWindow>
#include <QQuickWidget>
#include <QQuickWindow>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addUpdateButton(QAction *action);
    void setListViewModel(QStringListModel *model);

  private slots:

    void on_actionLoad_triggered();

    void on_actionshow_console_triggered(bool checked);

    void fullscreenShortcutActivated();

  private:
    Ui::MainWindow *ui;
};

