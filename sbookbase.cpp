#include "sbookbase.h"
#include <QRegularExpression>

SBookbase::SBookbase(QString filePath) {
    file.setFileName(filePath);
    obj_size = sbook_size;
}

QVector<Item*>* SBookbase::Read(int from, int to)
{
    QVector<Item*>* SBooks = new QVector<Item*>();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i = 0;

        while (i < (from - 1) * obj_size)
        {
            file.readLine();
            i++;
        }

        QByteArray rawLine;
        QString line;
        SerialBook* SBook;

        while (from <= to)
        {
            SBooks->append(new SerialBook(6));

            for (int i = 0; i < obj_size; i++)
            {
                rawLine = file.readLine();
                line = QString::fromUtf8(rawLine);
                line.remove('\n');
                SBook = dynamic_cast<SerialBook*>((*SBooks)[SBooks->size() - 1]);
                SBook->GetValues()[i] = line;

                if (i == obj_size - 1)
                {
                    QStringList list = line.split(" ", Qt::SkipEmptyParts);

                    foreach (QString num, list) SBook->GetIds()->append(num.toInt());
                }
            }

            from++;
        }
    }
    else qDebug() << "Error";

    file.close();

    return SBooks;
}

void SBookbase::Write(QVector<Item*>* books, int from, int to)
{
    if (from > books->size() || to > books->size()) return;

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QString* values;
        //QString symbol = "\n";

        //file.write(symbol.toUtf8());

        while (from <= to)
        {
            values = (*books)[from - 1]->GetValues();

            for (int i = 0; i < 6; i++)
            {
                file.write((values[i] + "\n").toUtf8());
            }

            from++;
        }
    }
    else qDebug() << "Error";

    file.close();
}

QVector<Item*>* SBookbase::Search(QString data, int type)
{ // Title: type 2, Author: 3, ID: type 4
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray rawData = (data + "\n").toUtf8();
        QByteArray* rawLines = new QByteArray[6];
        QVector<Item*>* items = new QVector<Item*>();

        while (!file.atEnd())
        {
            for (int i = 0; i < 6; i++)
            {
                if (file.atEnd())
                {
                    delete[] rawLines;
                    return nullptr;
                }

                rawLines[i] = file.readLine();
            }

            if (rawData == rawLines[type])
            {
                Item* item = new SerialBook(6);
                QString* values = item->GetValues();

                for (int i = 0; i < 6; i++)
                {
                    values[i] = QString::fromUtf8(rawLines[i]).remove("\n");
                }

                items->append(item);

                if (type != 3)
                {
                    file.close();
                    return items;
                }
            }
        }

        file.close();
        //delete[] rawLines;

        if (type == 3 && !(items->isEmpty())) return items;
    }

    //delete items;
    return nullptr;
}

bool SBookbase::Update(QString data, int type, QString desc)
{
    QByteArray rawLine;
    QString oldDesc;
    QString* text;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        rawLine = file.readAll();
        text = new QString(rawLine);

        int index = (*text).indexOf(data);
        index -= 2;

        while ((*text)[index - 1] != '\n') index--;
        while ((*text)[index] != '\n')
        {
            oldDesc += (*text)[index];
            index++;
        }

        //QRegularExpression reg(oldDesc);
        //(*text).replace(reg, desc);
        (*text).replace(oldDesc, desc);

        file.close();

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write(text->toUtf8());
            file.close();

            return 1;
        }
    }

    return 0;
}


bool SBookbase::Delete(QString data, int type)
{
    data += '\n';

    int startIndex = 0;
    if (type == 1) startIndex = 2;
    else if (type == 2) startIndex = 4;

    QStringList* text = new QStringList();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Type 1: title, Type 2: id
        while (!file.atEnd())
        {
            text->append(file.readLine());
        }

        file.close();

        for (int i = startIndex; i < text->size(); i += 6)
        {
            if ((*text)[i] == data)
            {
                int j = i - startIndex;
                int jLast = j + 6;
                for (j; j < jLast; j++)
                {
                    (*text)[j] = "";
                }
            }
        }

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for (int i = 0; i < text->size(); i++)
            {
                file.write((*text)[i].toUtf8());
            }
            file.close();

            delete text;
            return 1;
        }
    }

    delete text;
    return 0;
}
