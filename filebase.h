#ifndef FILEBASE_H
#define FILEBASE_H

#include <QFile>

class Item;

class Filebase {

public:
    virtual QVector<Item*>* Read(int, int) = 0;
    virtual void Write(QVector<Item*>*, int, int) = 0;
    virtual QVector<Item*>* Search(QString, int) = 0;
    virtual bool Update(QString, int, QString) = 0;
    virtual bool Delete(QString, int) = 0;

protected:
    QFile file;
    int obj_size;
};

#endif // FILEBASE_H
