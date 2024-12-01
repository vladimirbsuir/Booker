#include "featured.h"
#include "user.h"
#include "widget.h"
#include "mylabel.h"
#include "item.h"
//#include "mainwindow.h"

Featured::Featured(QWidget *parent, User* user, Widget* catalog, MainWindow* mainWindow)
    : QWidget{parent}
{
    this->mainWindow = mainWindow;
    this->catalog = catalog;
    this->user = user;

    area = new QScrollArea();
    grid = new QGridLayout();
    widget = new QWidget();

    //QVBoxLayout* vbox1 = new QVBoxLayout();

    //QLabel* label2 = new QLabel("Text2");
    //grid->addWidget(label2, 1, 0);
    //QLabel* label3 = new QLabel("Text3");
    //grid->addWidget(label3, 2, 1);

    //vbox1->addWidget(label2);
    //vbox1->addWidget(label3);
    //grid->addLayout(vbox1, 0, 1);

    //grid->setHorizontalSpacing(100);
    //grid->setVerticalSpacing(20);
    area->hide();
}

void Featured::SetBooks()
{
    // Delete widgets
    while(QLayoutItem *tmpItem = grid->itemAt(0)) {
        QVBoxLayout* vbox = dynamic_cast<QVBoxLayout*>(tmpItem);
        while (QLayoutItem* tmpItem2 = vbox->itemAt(0))
        {
            vbox->removeItem(tmpItem2);
            vbox->removeWidget(tmpItem2->widget());
            delete tmpItem2->widget();
            delete tmpItem2;
        }
        grid->removeItem(tmpItem);
        //grid->removeWidget(tmpItem->widget());
        delete tmpItem->widget();
        delete tmpItem;
        qDebug() << "Deleting\n";
    }
    grid->update();
    //grid->deleteLater();
    //grid = new QGridLayout();
    //

    int index = 0;

    featured = user->GetFeatured();
    //images = catalog->GetImages();
    //titles = catalog->GetTitles();
    books = catalog->GetBooks();
    sbooks = catalog->GetSBooks();
    QVector<Item*>* pBooks;
    int isSBook = 0;

    for (int i = 0; i < featured->size(); i++)
    {
        index = (*featured)[i].toInt();

        if (index >= 90)
        {
            index -= 90;
            pBooks = sbooks;
            isSBook = 1;
        }
        else
        {
            isSBook = 0;
            pBooks = books;
        }

        QPixmap im1((*pBooks)[index]->GetValues()[0]);
        QLabel* lb = new QLabel();
        //widgets->append(lb);
        //imageLabels.append(lb);
        QSize PicSize(500, 500);
        im1 = im1.scaled(PicSize, Qt::KeepAspectRatio);
        lb->setPixmap(im1);
        lb->setAlignment(Qt::AlignCenter);
        MyLabel* label = new MyLabel();
        //label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        //label->setFixedHeight(100);
        label->SetWType(2);
        label->setWordWrap(true);
        label->setText((*pBooks)[index]->GetValues()[2]); //
        if (isSBook) label->SetIndex(index + 90);
        else label->SetIndex(index); //

        label->SetWindow(this->mainWindow); //
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        QFont font = label->font();
        font.setPixelSize(35);
        label->setFont(font);
        QVBoxLayout* vbox = new QVBoxLayout();
        vbox->addWidget(lb);
        vbox->addWidget(label);

        grid->addLayout(vbox, i / 3, i % 3);
    }

    grid->setSizeConstraint(QLayout::SetFixedSize);
    grid->setHorizontalSpacing(100);
    grid->setVerticalSpacing(20);
    this->setLayout(grid);

    area->setWidget(this);
    area->resize(200, 200);
    //for (int i = 0; i < widgets->size(); i++) grid->removeWidget((*widgets)[i]);
}

QScrollArea* Featured::GetArea()
{
    return area;
}
