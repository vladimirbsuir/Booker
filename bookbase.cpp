#include "bookbase.h"
#include <QRegularExpression>

// Search, Update, Delete

#include <QDebug>

Bookbase::Bookbase(QString filePath) {
    file.setFileName(filePath);
    obj_size = book_size;
}

QVector<Item*>* Bookbase::Read(int from, int to)
{
    QVector<Item*>* books = new QVector<Item*>();

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
        Book* book;

        while (from <= to)
        {
            books->append(new Book(5));

            for (int i = 0; i < obj_size; i++)
            {
                rawLine = file.readLine();
                line = QString::fromUtf8(rawLine);
                line.remove('\n');
                book = dynamic_cast<Book*>((*books)[books->size() - 1]);
                book->GetValues()[i] = line;
            }

            from++;
        }
    }
    else qDebug() << "Error";

    file.close();

    return books;
}

void Bookbase::Write(QVector<Item*>* books, int from, int to)
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

            for (int i = 0; i < 5; i++)
            {
                file.write((values[i] + "\n").toUtf8());
            }

            from++;
        }
    }
    else qDebug() << "Error";

    file.close();
}

QVector<Item*>* Bookbase::Search(QString data, int type)
{ // Title: type 2, Author: type 3, ID: type 4
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray rawData = (data + "\n").toUtf8();
        QByteArray* rawLines = new QByteArray[5];
        QVector<Item*>* items = new QVector<Item*>();

        while (!file.atEnd())
        {
            for (int i = 0; i < 5; i++)
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
                Item* item = new Book(5);
                QString* values = item->GetValues();

                for (int i = 0; i < 5; i++)
                {
                    values[i] = QString::fromUtf8(rawLines[i]).remove("\n");
                }

                items->append(item);

                if (type != 3)
                {
                    file.close();
                    //delete[] rawLines;
                    return items;
                }
            }
        }

        file.close();
        //delete[] rawLines;

        if (type == 3 && !(items->isEmpty())) return items;
    }

    return nullptr;
    //delete items;
}

bool Bookbase::Update(QString data, int type, QString desc)
{
    QByteArray rawLine;
    QString oldDesc;
    QString* text;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Type 1: title, Type 2: id
        rawLine = file.readAll();
        text = new QString(rawLine);

        int index = (*text).indexOf(data);
        //if (!index) return 0;
        //index -= 2;
        qDebug() << index;

        int i = 0;
        if (type == 1)
        {
            //i = 1;
            index -= 2;
            while ((*text)[index - 1] != '\n') index--;
        }
        else if (type == 2)
        {
            //i = 3;
            while ((*text)[index] != '\n') index++;
            index++;
        }

        while ((*text)[index] != '\n')
        {
            oldDesc += (*text)[index];
            index++;
        }

        QRegularExpression reg(oldDesc);
        (*text).replace(reg, desc);

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

bool Bookbase::Delete(QString data, int type)
{
    data += '\n';

    int flag = 0;
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

        for (int i = startIndex; i < text->size(); i += 5)
        {
            if ((*text)[i] == data)
            {
                flag = 1;
                int j = i - startIndex;
                int jLast = j + 5;
                for (j; j < jLast; j++)
                {
                    (*text)[j] = "";
                }
            }
        }

        if (!flag)
        {
            delete text;
            return 0;
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
}
