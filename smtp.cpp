#include "smtp.h"


Smtp::Smtp(const QString& user, const QString& pass, const QString& host, int port, int timeout )
{
    socket = new QSslSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ErrorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(StateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));

    this->user = user;
    this->pass = pass;

    this->host = host;
    this->port = port;
    this->timeout = timeout;
}

void Smtp::SendMail(const QString &from, const QString &to, const QString &subject, const QString &body)
{
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append(body);
    message.replace(QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    message.replace(QString::fromLatin1( "\r\n.\r\n" ), QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHostEncrypted(host, port);
    if (!socket->waitForConnected(timeout))
    {
        qDebug() << socket->errorString();
    }

    sts = new QTextStream(socket);
}

Smtp::~Smtp()
{
    delete sts;
    delete socket;
}

void Smtp::StateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() <<"State was changed " << socketState;
}

void Smtp::ErrorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error: " << socketError;
}

void Smtp::Disconnected()
{
    qDebug() <<"Disconneted";
    qDebug() << "Error: "  << socket->errorString();
}

void Smtp::Connected()
{
    qDebug() << "Connected";
}

void Smtp::ReadyRead()
{
    qDebug() <<"Ready to read";

    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while (socket->canReadLine() && responseLine[3] != ' ');

    responseLine.truncate(3);

    qDebug() << "Server response code: " <<  responseLine;
    qDebug() << "Server response: " << response;

    if (state == Init && responseLine == "220")
    {
        *sts << "EHLO localhost" <<"\r\n";
        sts->flush();

        state = HandShake;
    }
    else if (state == HandShake && responseLine == "250")
    {
        socket->startClientEncryption();
        if(!socket->waitForEncrypted(timeout))
        {
            qDebug() << socket->errorString();
            state = Close;
        }

        *sts << "EHLO localhost" << "\r\n";
        sts->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        qDebug() << "Auth";
        *sts << "AUTH LOGIN" << "\r\n";
        sts->flush();
        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        qDebug() << "Username";

        *sts << QByteArray().append(user.toLocal8Bit().data()).toBase64()  << "\r\n";
        sts->flush();

        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        //QString p = "fsqe xltf gvdp uthu";
        qDebug() << "Pass";
        *sts << QByteArray().append(pass.toLocal8Bit().data()).toBase64() << "\r\n";
        sts->flush();

        state = Mail;
    }
    else if (state == Mail && responseLine == "235")
    {
        //qDebug() << "MAIL FROM:<" << from << ">";
        *sts << "MAIL FROM:<" << from << ">\r\n";
        sts->flush();
        state = Rcpt;
    }
    else if (state == Rcpt && responseLine == "250")
    {
        *sts << "RCPT TO:<" << rcpt << ">\r\n"; //r
        sts->flush();
        state = Data;
    }
    else if (state == Data && responseLine == "250")
    {
        *sts << "DATA\r\n";
        sts->flush();
        state = Body;
    }
    else if (state == Body && responseLine == "354")
    {
        *sts << message << "\r\n.\r\n";
        sts->flush();
        state = Quit;
    }
    else if (state == Quit && responseLine == "250")
    {
        *sts << "QUIT\r\n";
        sts->flush();
        state = Close;
        emit status(tr("Message sent"));
    }
    else if (state == Close)
    {
        deleteLater();
        return;
    }
    else
    {
        QMessageBox::warning(0, tr("SMTP"), tr("Unexpected reply from SMTP server:\n\n") + response);
        state = Close;
        emit status(tr("Failed to send message"));
    }
    response = "";
}
