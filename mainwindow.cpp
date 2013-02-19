#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cc = new ClientConnection(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cc;
}
