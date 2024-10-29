#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>

class User
{
public:
    User();

    QString GetLogin();
    QString GetPass();
    QString GetImage();
    QStringList* GetFeatured();
    void SetLogin(QString);
    void SetPass(QString);
    void SetImage(QString);
    void SetFeatured(QStringList*);

private:
    QString login;
    QString pass;
    QString image;
    QStringList* featured;
};

#endif // USER_H
