#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addUpdateButton(QAction *action)
{
    ui->toolBar->addAction(action);
}

void MainWindow::on_quickWidget_sceneGraphError(const QQuickWindow::SceneGraphError &error, const QString &message)
{
    qDebug() << "error" << message;
}

void MainWindow::on_quickWidget_statusChanged(const QQuickWidget::Status &arg1)
{
    qDebug() << "status change" << arg1;
}

void MainWindow::on_actionLoad_triggered()
{
    qDebug() << "action triggered";
}

void MainWindow::on_actionshow_console_triggered(bool checked)
{
    if(checked){
        ui->textEdit->show();
    }else{
        ui->textEdit->hide();
    }
}
