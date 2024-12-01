#ifndef SBOOKBASE_H
#define SBOOKBASE_H

#include "filebase.h"
#include "serialbook.h"

#define sbook_size 6

class SBookbase : public Filebase
{
public:
    SBookbase(QString);
    SBookbase();

    QVector<Item*>* Read(int, int) override;
    void Write(QVector<Item*>*, int, int) override;
    QVector<Item*>* Search(QString, int) override;
    bool Update(QString, int, QString) override;
    bool Delete(QString, int) override;
};

#endif // SBOOKBASE_H
