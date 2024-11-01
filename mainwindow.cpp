#include "mainwindow.h"
#include "widget.h"
#include "user.h"
#include "profile.h"
#include "myimagelabel.h"
#include "featured.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    user = new User();
    database = new Database(user);

    catalog = new Widget(nullptr, this);
    hbox = new QHBoxLayout();
    page = new BookPage(nullptr, catalog, user);

    //catalog->SetMainW(this);

    profile = new Profile(nullptr, database, user);

    // Featured
    featured = new Featured(nullptr, user, catalog, this);

    // Menu
    menu = new Menu(nullptr, catalog, profile, page, database, user, featured);
    menu->hide();
    // -------------------------------

    regAuth = new RegAuthPage(nullptr, catalog, menu, database, user, profile);



    /*QWidget* w3 = new QWidget();
    QLabel* labb = new QLabel("Labbb");
    QVBoxLayout* vbox2 = new QVBoxLayout();
    vbox2->addWidget(labb);
    w3->setLayout(vbox2);*/

    hbox->addWidget(regAuth);
    hbox->addWidget(menu);
    hbox->addWidget(catalog->GetArea());
    hbox->addWidget(page);
    hbox->addWidget(profile);
    hbox->addWidget(featured->GetArea());
    page->hide();
    profile->hide();
    hbox->setContentsMargins(0,0,0,0);
    hbox->setSpacing(0);
    //hbox->addWidget(w3);

    //catalog->GetTitles();

    this->setLayout(hbox);

    //catalog->GetArea()->hide();

    //w3->show();
    //catalog->GetArea()->show();
    catalog->GetArea()->hide();
    this->show();
}

void MainWindow::SetBookPage(int index)
{
    int isFeatured = 0;
    QVector<QString>* titles = catalog->GetTitlesV();
    QVector<QString>* images = catalog->GetImagesV();
    QVector<QString>* desc = catalog->GetDescV();
    QVector<QString>* authors = catalog->GetAuthorsV();

    page->GetTitle()->setText((*titles)[index] + " | " + (*authors)[index]);
    page->GetDesc()->setText((*desc)[index]);
    page->GetImage()->setAlignment(Qt::AlignCenter);
    page->GetTitle()->setAlignment(Qt::AlignCenter);

    page->SetIndex(index);
//
    QPixmap im((*images)[index]);
    QSize PicSize(300, 500);
    im = im.scaled(PicSize, Qt::KeepAspectRatio);
    page->GetImage()->setPixmap(im);
//
    QStringList* featured = user->GetFeatured();
    if (!featured->isEmpty())
    {
        if (featured->contains(QString::number(index))) isFeatured = 1;
        else isFeatured = 0;
    }
    else isFeatured = 0;

    QPixmap featImage;
    if (isFeatured) featImage.load("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddedToFeatured.jpg");
    else featImage.load("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddToFeatured.jpg");
    page->SetState(isFeatured);

    QSize featSize(50, 50);
    featImage = featImage.scaled(featSize, Qt::KeepAspectRatio);
    page->GetFeatureImage()->setPixmap(featImage);

    catalog->GetArea()->hide();
    page->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    database->UpdateUser(user->GetFeatured()->join(" "), 3);
    event->accept();
}
