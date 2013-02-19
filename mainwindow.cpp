#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cc = new ClientConnection(this);
    connect(cc, SIGNAL(signalConectado()), this, SLOT(confirmConnected()));
    connect(cc, SIGNAL(signalDesconectado()), this, SLOT(confirmDisconnected()));
    connect(cc, SIGNAL(newStringMessage(QString)), this, SLOT(processStringMessage(QString)));
    connect(cc, SIGNAL(newStringAndImage(QString,QImage)), this, SLOT(processImage(QString,QImage)));
    connect(cc, SIGNAL(connectionError(QString,QString)), this, SLOT(processError(QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cc;
}

void MainWindow::confirmConnected(){

}

void MainWindow::confirmDisconnected(){

}


void MainWindow::processError(QString tittle, QString body){

}

void MainWindow::processStringMessage(QString message){

}

void MainWindow::processImage(QString message, QImage img){

}
