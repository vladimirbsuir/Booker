#include "searchingitems.h"
#include "item.h"
#include "mylabel.h"


SearchingItems::SearchingItems(QWidget *parent, MainWindow* mainWindow)
    : QWidget{parent}
{
    this->mainWindow = mainWindow;

    area = new QScrollArea();
    grid = new QGridLayout();

    area->hide();
}

void SearchingItems::SetItems(QVector<Item*>* items)
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
        delete tmpItem->widget();
        delete tmpItem;
    }
    grid->update();

    for (int i = 0; i < items->size(); i++)
    {
        QPixmap im1((*items)[i]->GetValues()[0]);
        QLabel* lb = new QLabel();
        QSize PicSize(500, 500);
        im1 = im1.scaled(PicSize, Qt::KeepAspectRatio);
        lb->setPixmap(im1);
        lb->setAlignment(Qt::AlignCenter);
        MyLabel* label = new MyLabel();
        label->SetWType(3);
        label->setWordWrap(true);
        label->setText((*items)[i]->GetValues()[2]); //
        label->SetIndex((*items)[i]->GetValues()[4].toInt());

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
    grid->setHorizontalSpacing(250);
    grid->setVerticalSpacing(20);
    this->setLayout(grid);

    area->setWidget(this);
    //area->resize(200, 200);
    area->show();
}

QScrollArea* SearchingItems::GetArea()
{
    return area;
}
