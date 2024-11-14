#ifndef BOOKBASE_H
#define BOOKBASE_H

#include "filebase.h"
#include "book.h"

#define book_size 5

class Bookbase : public Filebase
{
public:
    Bookbase(QString);
    Bookbase();

    QVector<Item*>* Read(int, int) override;
    void Write(QVector<Item*>*, int, int) override;
    Item* Search(QString) override;
    //bool Update(QString, QString) override;
};

#endif // BOOKBASE_H
