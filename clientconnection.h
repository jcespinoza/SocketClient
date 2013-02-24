#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <QObject>
#include <QDebug>
#include <QImage>
#include <QTcpSocket>

class ClientConnection: public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent=0);

    void sendMessage(QString);
    void conectar(QString, int port);
    void desconectar();
    ~ClientConnection();
    bool isConnected(){return estaConectado;}
private:
    QTcpSocket *socket;
    quint32 dataSize;
    bool estaConectado;
    QByteArray arrayData;
    QString user, pass;
    void parseMessage(QByteArray);
private slots:
    void recibirData();
    void conectado();
    void displayError(QAbstractSocket::SocketError);
    void desconectado();
signals:
    void connectionError(QString, QString);
    void signalConectado();
    void signalDesconectado();
    void newStringMessage(QString);
    void newStringAndImage(QString, QImage);

};

#endif // CLIENTCONNECTION_H
