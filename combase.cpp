#include "combase.h"

Combase::Combase() {
    db = QSqlDatabase::addDatabase("QSQLITE", "DB2");
    db.setDatabaseName("./comments.db");
    query = new QSqlQuery(db);
    db.open();

    query->exec("CREATE TABLE IF NOT EXISTS Comments(title TEXT, user_login TEXT, comment TEXT, rating INTEGER);");
}

void Combase::InsertComment(QString title, QString user_login, QString comment, int rating)
{
    query->prepare("INSERT INTO Comments(title, user_login, comment, rating) VALUES(:title, :user_login, :comment, :rating);");
    query->bindValue(":title", title);
    query->bindValue(":user_login", user_login);
    query->bindValue(":comment", comment);
    query->bindValue(":rating", rating);
    query->exec();

    //qDebug() << title << " " << user_login << " " << comment << " " << rating;
}

void Combase::UpdateComment(QString title, QString user_login, QString comment, int rating)
{
    query->prepare("UPDATE Comments SET comment = :comment, rating = :rating WHERE title = :title AND user_login = :user_login");
    query->bindValue(":title", title);
    query->bindValue(":user_login", user_login);
    query->bindValue(":comment", comment);
    query->bindValue(":rating", rating);
    query->exec();
}

QVector<QString>* Combase::GetComments(QString title)
{
    query->prepare("SELECT user_login, comment, rating FROM Comments WHERE title = :title");
    query->bindValue(":title", title);
    query->setForwardOnly(true);
    query->exec();
    //query->first();
    QVector<QString>* data = new QVector<QString>();

    while (query->next())
    {
        qDebug() << query->value(0).toString() << " " << query->value(1).toString() << " " << query->value(2).toString();
        data->append(query->value(0).toString());
        data->append(query->value(1).toString());
        data->append(query->value(2).toString());
    }

    return data;
}
