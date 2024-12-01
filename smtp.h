#ifndef SMTP_H
#define SMTP_H

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>


class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp(const QString &user, const QString &pass, const QString &host, int port = 465, int timeout = 30000);
    ~Smtp();

    void SendMail(const QString &from, const QString &to, const QString &subject, const QString &body);

signals:
    void status(const QString&);

private slots:
    void StateChanged(QAbstractSocket::SocketState);
    void ErrorReceived(QAbstractSocket::SocketError);
    void Disconnected();
    void Connected();
    void ReadyRead();

private:
    int timeout;
    QString message;
    QTextStream* sts;
    QSslSocket* socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    enum states{Tls, HandShake, Auth, User, Pass, Rcpt, Mail, Data, Init, Body, Quit, Close};
    int state;
};

#endif
