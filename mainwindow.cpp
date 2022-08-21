#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QShortcut *fullscreenHotKey = new QShortcut(QKeySequence(Qt::Key_F11), this);
    fullscreenHotKey->setContext(Qt::ApplicationShortcut);

    QObject::connect(fullscreenHotKey, &QShortcut::activated,
                     this, &MainWindow::fullscreenShortcutActivated);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addUpdateButton(QAction *action) {
    ui->toolBar->addAction(action);
}

void MainWindow::setListViewModel(QStringListModel *model) {
    ui->listView->setModel(model);
}

void MainWindow::on_actionLoad_triggered() {
    qDebug() << "action triggered";
}

void MainWindow::on_actionshow_console_triggered(bool checked) {
    if(checked) {
        ui->listView->show();
    } else {
        ui->listView->hide();
    }
}

void MainWindow::fullscreenShortcutActivated() {
    if(this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}
