#include "bookbase.h"

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

Item* Bookbase::Search(QString title)
{
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray rawTitle = (title + "\n").toUtf8();
        QByteArray* rawLines = new QByteArray[5];

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

            if (rawTitle == rawLines[2])
            {
                Item* item = new Book(5);
                QString* values = item->GetValues();

                for (int i = 0; i < 5; i++)
                {
                    values[i] = QString::fromUtf8(rawLines[i]).remove("\n");
                }

                file.close();
                return item;
            }
        }

        file.close();
        delete[] rawLines;

        return nullptr;
    }
}

/*bool Bookbase::Update(QString title, QString desc)
{
    QByteArray rawTitle = (title + "\n").toUtf8();
    QByteArray rawLine;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        rawLine = file.readAll();
        QString text(rawLine);
    }
}*/
