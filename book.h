#ifndef BOOK_H
#define BOOK_H

#include <QString>

#include "item.h"

class Book : public Item
{

public:
    QString GetImage();
    QString GetTitle();
    QString GetDesc();
    QString GetAuthor();
    QString GetId();
    void SetImage(QString);
    void SetTitle(QString);
    void SetDesc(QString);
    void SetAuthor(QString);
    void SetId(QString);

    Book(int);

private:
    /*QString image;
    QString title;
    QString desc;
    QString author;
    QString id;*/
    //QString values[5];
};

#endif // BOOK_H
