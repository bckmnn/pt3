#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/logger.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

#ifdef Q_OS_MAC
    QShortcut *fullscreenHotKey = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this);
#else
    QShortcut *fullscreenHotKey = new QShortcut(QKeySequence(Qt::Key_F11), this);
#endif
    fullscreenHotKey->setContext(Qt::ApplicationShortcut);
    QObject::connect(fullscreenHotKey, &QShortcut::activated,
                     this, &MainWindow::fullscreenShortcutActivated);

#ifdef Q_OS_MAC
    QShortcut *totalFullscreenHotKey = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F), this);
#else
    QShortcut *totalFullscreenHotKey = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F11), this);
#endif

    totalFullscreenHotKey->setContext(Qt::ApplicationShortcut);
    QObject::connect(totalFullscreenHotKey, &QShortcut::activated,
                     this, &MainWindow::totalFullscreenShortcutActivated);

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

void MainWindow::restoreWindow() {
    ui->mainWinHorizontalLayout->setMargin(9);
    if(ui->actionshow_console->isChecked()) {
        ui->toolBox->show();
    }
    ui->toolBar->show();
    this->showNormal();
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
        restoreWindow();
    } else {
        this->showFullScreen();
    }
}

void MainWindow::totalFullscreenShortcutActivated() {
    if(this->isFullScreen()) {
        restoreWindow();
    } else {
        ui->mainWinHorizontalLayout->setMargin(0);
        if(ui->actionshow_console->isChecked()) {
            ui->toolBox->hide();
        }
        ui->toolBar->hide();
        this->showFullScreen();
    }
}

void MainWindow::consoleModelReset() {
    ui->consoleListView->scrollToBottom();
}

void MainWindow::on_btnClearConsole_clicked() {
    Logger::clearMessages();
}
