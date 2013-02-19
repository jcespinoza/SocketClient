#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    ClientConnection *cc;
private slots:
    void confirmConnected();
    void confirmDisconnected();
    void processError(QString, QString);
    void processStringMessage(QString);
    void processImage(QString, QImage);
    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();
    void on_leCommand_returnPressed();
};

#endif // MAINWINDOW_H
