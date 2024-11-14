#include "widget.h"
#include "mylabel.h"
#include "mainwindow.h"

#include "bookbase.h"

#include <QMessageBox>

#define filePath "D:\\University\\Course Work\\BookerClass\\Data\\data.txt"
#define rows 3
#define cols 3
#define btnsAmount 9
#define booksAmount 9
#define booksInFile 60
#define fontSize 35

Widget::Widget(QWidget *parent, MainWindow* wind)
    : QWidget(parent)
{
    this->mainw = wind;
    currentPage = 1;

    // Test bookbase
    Bookbase* bookbase = new Bookbase("D:\\University\\Course Work\\BookerClass\\Data\\testbooks.txt");
    QVector<Item*>* books = bookbase->Read(2, 2);

    QString* bookValues;
    for (int i = 0; i < books->size(); i++)
    {
        bookValues = (*books)[i]->GetValues();
        for (int j = 0; j < 5; j++)
        {
            qDebug() << bookValues[j];
        }
    }

    bookbase->Write(books, 1, books->size());

    Item* item = bookbase->Search("Far Cry 5");
    qDebug() << "Founded book:";
    for (int i = 0; i < 5; i++)
    {
        qDebug() << item->GetValues()[i];
    }

    //

    QFile file(filePath);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        /*size_t l = 8;
        for (size_t i = 0; i < l; i++)
        {
            file.readLine();
        }*/



        while (!file.atEnd())
        {
            //
            rawLine = file.readLine();
            line = QString::fromUtf8(rawLine);
            line.remove('\n');
            images.append(line);
            //
            rawLine = file.readLine();
            line = QString::fromUtf8(rawLine);
            line.remove('\n');
            desc.append(line);
            //
            rawLine = file.readLine();
            line = QString::fromUtf8(rawLine);
            line.remove('\n');
            titles.append(line);
            //
            rawLine = file.readLine();
            line = QString::fromUtf8(rawLine);
            line.remove('\n');
            authors.append(line);
            //
            rawLine = file.readLine();
            line = QString::fromUtf8(rawLine);
            line.remove('\n');
            id.append(line);
        }

        //QByteArray rawLine = file.readLine();
        file.close();

        //line = QString::fromUtf8(rawLine);
        //line.remove('\n');
    }

    for (size_t i = 0; i < titles.size(); i++)
    {
        qDebug() << titles[i] << Qt::endl;
    }

    //qDebug() << "a";
    //qDebug() << line;

    grid = new QGridLayout();


    //QVector<QLabel*> labels;
    //QVector<QPushButton*> btns;
    //QVector<QVBoxLayout*> vboxes;

    /*for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            QPushButton* btn = new QPushButton();
            QLabel* label = new QLabel("label");
            QVBoxLayout* vbox = new QVBoxLayout();
            vbox->addWidget(btn);
            vbox->addWidget(label);
            labels.append(label);

            btns.append(btn);
            labels.append(label);
            grid->addLayout(vbox, i, j);

        }
    }*/

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            QPixmap im1(images[i * cols + j]);
            QLabel* lb = new QLabel();
            imageLabels.append(lb);
            QSize PicSize(500, 500);
            im1 = im1.scaled(PicSize, Qt::KeepAspectRatio);
            lb->setPixmap(im1);
            lb->setAlignment(Qt::AlignCenter);
            MyLabel* label = new MyLabel();
            label->SetWType(1);
            label->setWordWrap(true);
            myLabels.append(label);
            label->setText(titles[i * cols + j]); //
            label->SetIndex(i * cols + j); //
            //QWidget* wwww = this->parentWidget();
            //qDebug() << qobject_cast<MainWindow*>(this->parentWidget());
            //qDebug() << qobject_cast<MainWindow*>(this->mainw);
            label->SetWindow(this->mainw); //
            label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            label->setAlignment(Qt::AlignCenter);
            QFont font = label->font();
            font.setPixelSize(fontSize);
            label->setFont(font);
            QVBoxLayout* vbox = new QVBoxLayout();
            vbox->addWidget(lb);
            vbox->addWidget(label);
            //labels.append(label);

            //btns.append(lb);
            //labels.append(label);
            grid->addLayout(vbox, i, j);
        }
    }

    QPixmap im1("D:\\University\\Course Work\\BookerClass\\Data\\Images\\Image.png");

    QLabel* lb = new QLabel();
    QSize PicSize(100, 100);
    im1 = im1.scaled(PicSize, Qt::KeepAspectRatio);
    lb->setPixmap(im1);
    QLabel* label = new QLabel("label");
    //label->SetIndex(i * 1 + j);
    QVBoxLayout* vbox = new QVBoxLayout();
    label->setBuddy(lb);
    vbox->addWidget(lb);
    vbox->addWidget(label);
    //labels.append(label);

    //qDebug() << labels.size();


    btn = new QPushButton();
    connect(btn, SIGNAL(clicked()), SLOT(on_btn_clicked()));
    vbox->addWidget(btn);

    //grid->addLayout(vbox, 4, 0);

    // Buttons in catalog

    btnsLayout = new QHBoxLayout();
    btnsLayout->addStretch(1);
    for (int i = 1; i <= btnsAmount; i++)
    {
        QPushButton* btnAdd = new QPushButton(QString::number(i));
        pageBtns.append(btnAdd);
        connect(btnAdd, SIGNAL(clicked()), SLOT(on_pageBtn_clicked()));
        btnsLayout->addWidget(btnAdd);
    }
    btnsLayout->addStretch(1);
    grid->addLayout(btnsLayout, 4, 0, 4, 3);
    //
    grid->setHorizontalSpacing(100);
    grid->setVerticalSpacing(20);

    this->setLayout(grid);

    area = new QScrollArea();
    area->setWidget(this);
    area->resize(200, 200);

    //area->setContentsMargins(0,0,0,0);

    //qDebug() << grid->count();

    //area->show();
}

Widget::~Widget() {}

void Widget::on_pageCatBtn_clicked(int goTo)
{
    if (currentPage == goTo)
    {
        QMessageBox::about(this, "Warning", "You are already at this page");
        return;
    }
    else if (goTo > 50)
    {
        QMessageBox::about(this, "Warning", "Page number is out of range");
        return;
    }

    currentPage = goTo;
    ChangeBtns(0, currentPage);

    int startBook = (currentPage - 1) * booksAmount;


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i * cols + j + startBook >= booksInFile) return;

            QPixmap im1(images[i * cols + j + startBook]);
            QSize PicSize(500, 500);
            im1 = im1.scaled(PicSize, Qt::KeepAspectRatio);
            imageLabels[i * cols + j]->setPixmap(im1);
            myLabels[i * cols + j]->setText(titles[i * cols + j + startBook]);
            myLabels[i * cols + j]->SetIndex(i * cols + j + startBook); //
        }
    }
}

void Widget::ChangeBtns(int modifier, int firstN)
{
    area->ensureVisible(0,0);

    if (firstN == 50) firstN -= 8;
    else if (firstN > 41) firstN -= 7;
    else if (firstN > 1) firstN--; //

    if (firstN == 0) firstN = pageBtns[0]->text().toInt();
    else middlePage = (firstN * 2 + 9) / 2;

    qDebug() << middlePage << " ";

    for (int i = 0; i < 9; i++)
    {
        pageBtns[i]->setText(QString::number(firstN + i + modifier));
    }
}

void Widget::on_pageBtn_clicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());

    if (clickedBtn)
    {
        //area->ensureVisible(0,0);

        int page = clickedBtn->text().toInt(0, 10);
        if (currentPage == page) return;

        currentPage = page;
        if ((currentPage > middlePage) && (middlePage + 4 < 50))
        {
            ChangeBtns(1);
            middlePage++;
        }
        else if ((currentPage < middlePage) && (middlePage - 4 > 1))
        {
            ChangeBtns(-1);
            middlePage--;
        }
        //qDebug() << cur

        int startBook = (currentPage - 1) * booksAmount;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (i * cols + j + startBook >= booksInFile) return;

                QPixmap im1(images[i * cols + j + startBook]);
                QSize PicSize(500, 500);
                im1 = im1.scaled(PicSize, Qt::KeepAspectRatio);
                //lb->setPixmap(im1);
                imageLabels[i * cols + j]->setPixmap(im1);
                //lb->setAlignment(Qt::AlignCenter);
                //MyLabel* label = new MyLabel();
                myLabels[i * cols + j]->setText(titles[i * cols + j + startBook]);
                //label->setText(titles[i * cols + j]); //
                myLabels[i * cols + j]->SetIndex(i * cols + j + startBook); //
                //QWidget* wwww = this->parentWidget();
                //qDebug() << qobject_cast<MainWindow*>(this->parentWidget());
                //qDebug() << qobject_cast<MainWindow*>(this->mainw);
                //label->SetWindow(this->mainw); //
                //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                //label->setAlignment(Qt::AlignCenter);
                //QFont font = label->font();
                //font.setPixelSize(50);
                //label->setFont(font);
                //QVBoxLayout* vbox = new QVBoxLayout();
                //vbox->addWidget(lb);
                //vbox->addWidget(label);
                //labels.append(label);

                //btns.append(lb);
                //labels.append(label);
                //grid->addLayout(vbox, i, j);
            }
        }
    }
}

void Widget::on_btn_clicked()
{
    qDebug() << "a";

    b = new QVBoxLayout();
    lab = new QLabel("Label");
    //lab->setText("Hello!");
    b->addWidget(lab);
    //w2 = new QWidget();
    //w2->setLayout(b);

    //w2->show();;

    qDeleteAll(this->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
    delete this->layout();
    this->setLayout(b);
    this->update();

    //labels[labels.size() - 1]->setText("Hello");
    //area->widget()->deleteLater();
    //area->setWidget(w2);
    //labels[0]->setText("Hello");
    //qDebug() << labels.size();
    qDebug() << grid->count();
    //area->update();
}

QScrollArea* Widget::GetArea()
{
    return area;
}

QVector<QString>* Widget::GetTitlesV()
{
    //qDebug() << "c";
    return &titles;
}

QVector<QString> Widget::GetTitles()
{
    return titles;
}

QVector<QString> Widget::GetImages()
{
    return images;
}

QVector<QString>* Widget::GetDescV()
{
    return &desc;
}

QVector<QString>* Widget::GetImagesV()
{
    return &images;
}

QVector<QString>* Widget::GetAuthorsV()
{
    return &authors;
}

void Widget::SetMainW(MainWindow* widget)
{
    this->mainw = widget;
    qDebug() << this->mainw;
}
