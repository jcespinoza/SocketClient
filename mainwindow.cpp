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
    ui->pbConnect->setDisabled(true);
    ui->pbDisconnect->setDisabled(false);
    ui->teMessages->append("Conexion aceptada...");
}

void MainWindow::confirmDisconnected(){
    ui->pbConnect->setDisabled(false);
    ui->pbDisconnect->setDisabled(true);
    ui->teMessages->append("Conexion cerrada...");
}


void MainWindow::processError(QString tittle, QString body){

}

void MainWindow::processStringMessage(QString message){
    ui->teMessages->append("NewStringMessage: " + message);
    ui->lbImage->clear();
}

void MainWindow::processImage(QString message, QImage img){

}

void MainWindow::on_pbConnect_clicked()
{
    cc->conectar(ui->leHost->text(), ui->lePort->text().toInt());
}

void MainWindow::on_pbDisconnect_clicked()
{

}

void MainWindow::on_leCommand_returnPressed()
{
    if(cc->isConnected()){
        cc->sendMessage(ui->leCommand->text() + "\n\r");
        ui->leCommand->clear();
    }
}
