#ifndef FILEBASE_H
#define FILEBASE_H

#include <QFile>

class Item;

class Filebase {

public:
    virtual QVector<Item*>* Read(int, int) = 0;
    virtual void Write(QVector<Item*>*, int, int) = 0;
    virtual Item* Search(QString) = 0;
    //virtual bool Update(QString, QString);

protected:
    QFile file;
    int obj_size;
};

#endif // FILEBASE_H
