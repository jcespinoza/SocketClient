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
    delete cc;
    delete ui;
}

void MainWindow::confirmConnected(){
    ui->pbConnect->setDisabled(true);
    ui->pbDisconnect->setDisabled(false);
    ui->teMessages->append("Conexion aceptada...");
    cc->sendMessage("LOGIN:"+ui->leUser->text()+ ":" +ui->lePass->text()+"\n\r");
    ui->teMessages->append("Login in with " + ui->leUser->text() + " And " + ui->lePass->text());
}

void MainWindow::confirmDisconnected(){
    ui->pbConnect->setDisabled(false);
    ui->pbDisconnect->setDisabled(true);
    ui->teMessages->append("Conexion cerrada...");
}


void MainWindow::processError(QString title, QString body){
    ui->teMessages->append(title + ":" + body);
}

void MainWindow::processStringMessage(QString message){
    ui->teMessages->append("Mensaje: " + message);
    ui->lbImage->clear();
}

void MainWindow::processImage(QString message, QImage img){
    ui->teMessages->append(message);
    if( !img.isNull() )
    {
        ui->lbImage->setPixmap(QPixmap::fromImage(img));
    }
    else
        this->ui->lbImage->setText( "Invalid image received!" );
}

void MainWindow::on_pbConnect_clicked()
{
    cc->conectar(ui->leHost->text(), ui->lePort->text().toInt());
}

void MainWindow::on_pbDisconnect_clicked()
{
    cc->desconectar();
}

void MainWindow::on_leCommand_returnPressed()
{
    if(cc->isConnected()){
        cc->sendMessage(ui->leCommand->text() + "\n\r");
        ui->leCommand->clear();
    }
}
