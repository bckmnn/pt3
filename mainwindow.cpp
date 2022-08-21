#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/logger.h"
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
    ui->consoleListView->setModel(model);
    QObject::connect(model, &QAbstractListModel::modelReset,
                     this, &MainWindow::consoleModelReset);
}

void MainWindow::on_actionLoad_triggered() {
    qDebug() << "action triggered";
}

void MainWindow::on_actionshow_console_triggered(bool checked) {
    if(checked) {
        ui->toolBox->show();
    } else {
        ui->toolBox->hide();
    }
}

void MainWindow::fullscreenShortcutActivated() {
    if(this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

void MainWindow::consoleModelReset() {
    ui->consoleListView->scrollToBottom();
}

void MainWindow::on_btnClearConsole_clicked() {
    Logger::clearMessages();
}
