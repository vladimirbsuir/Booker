#ifndef COMBASE_H
#define COMBASE_H

#include "obase.h"

class Combase : public OBase
{
public:
    void InsertComment(QString, QString, QString, int);
    void UpdateComment(QString, QString, QString, int);
    QVector<QString>* GetComments(QString);

    Combase();

private:
    int com_amount;
    //QSqlDatabase db;
    //QSqlQuery* query;
};

#endif // COMBASE_H
