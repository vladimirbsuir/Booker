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
    QVector<Item*>* Search(QString, int) override;
    bool Update(QString, int, QString) override;
    bool Delete(QString, int) override;
};

#endif // BOOKBASE_H
