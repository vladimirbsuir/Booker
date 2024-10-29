#include "bookpage.h"
#include "widget.h"
#include "myimagelabel.h"
#include "user.h"

BookPage::BookPage(QWidget *parent, Widget* catal, User* user)
    : QWidget{parent}
{
    this->catal = catal;
    this->user = user;

    hbox = new QHBoxLayout();
    vbox1 = new QVBoxLayout();
    //vbox1->SetFixedSize(100, 100);
    vbox2 = new QVBoxLayout();
    title = new QLabel();
    desc = new QLabel();
    image = new QLabel();
    btn = new QPushButton("Back");
    featureImage = new MyImageLabel(nullptr, this);
    //featureImage->setText("There should be a picture");
    connect(btn, SIGNAL(clicked()), SLOT(on_btn_clicked()));
    //vbox1->setSpacing(0);

    vbox1->addWidget(image);
    vbox1->addWidget(title);
    vbox1->addWidget(featureImage);
    vbox1->addStretch(1);
    vbox1->addWidget(btn);

    vbox2->addWidget(desc);
    hbox->addLayout(vbox1);
    hbox->addLayout(vbox2);

    this->setLayout(hbox);
}

void BookPage::SetIndex(int index)
{
    this->index = index;
}

void BookPage::SetState(int state)
{
    this->state = state;
    qDebug() << this->state;
}

MyImageLabel* BookPage::GetFeatureImage()
{
    return this->featureImage;
}

QLabel* BookPage::GetTitle()
{
    return this->title;
}

QLabel* BookPage::GetImage()
{
    return this->image;
}

QLabel* BookPage::GetDesc()
{
    return this->desc;
}

int BookPage::GetState()
{
    return this->state;
}

void BookPage::on_btn_clicked()
{
    this->hide();
    catal->GetArea()->show();
}

void BookPage::ChangeFeatureImage()
{
    qDebug() << this->state;
    QPixmap map;

    if (state == 0)
    {
        map.load("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddedToFeatured.jpg");
        state = 1;
        user->GetFeatured()->append(QString::number(index));
    }
    else
    {
        map.load("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddToFeatured.jpg");
        state = 0;
        user->GetFeatured()->remove(user->GetFeatured()->indexOf(QString::number(index)));
        user->GetFeatured()->squeeze();
    }

    QSize featSize(50, 50);
    map = map.scaled(featSize, Qt::KeepAspectRatio);
    featureImage->setPixmap(map);
}
