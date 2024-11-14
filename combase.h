#ifndef COMBASE_H
#define COMBASE_H

#include <QSqlDatabase>
#include <QSqlQuery>

class Combase
{
public:
    void InsertComment(QString, QString, QString, int);
    void UpdateComment(QString, QString, QString, int);
    QVector<QString>* GetComments(QString);

    Combase();

private:
    QSqlDatabase db;
    QSqlQuery* query;
};

#endif // COMBASE_H
