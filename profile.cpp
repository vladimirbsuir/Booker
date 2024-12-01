#include "profile.h"
#include "changeinfodialog.h"
#include "user.h"
#include "additemdialog.h"
#include "updateitemdialog.h"
#include "deleteitemdialog.h"

Profile::Profile(QWidget *parent, Database* database, User* user, Widget* catalog)
    : QWidget{parent}
{
    this->database = database;
    this->user = user;
    this->catalog = catalog;

    hbox = new QHBoxLayout();
    hbox2 = new QHBoxLayout();
    vbox = new QVBoxLayout();
    vbox2 = new QVBoxLayout();
    vboxMain = new QVBoxLayout();
    image = new QLabel();
    login = new QLabel();
    changeBtn = new QPushButton("Change your info");
    quitBtn = new QPushButton("Quit from account");
    addItemBtn = new QPushButton("Add item");
    updateItemBtn = new QPushButton("Update item");
    deleteItemBtn = new QPushButton("Delete item");
    updateItemBtn->hide();
    deleteItemBtn->hide();
    addItemBtn->hide();

    login->setWordWrap(true);
    login->setFixedWidth(300);
    login->setStyleSheet("font-size: 50px");

    changeBtn->setFixedSize(250, 100);
    quitBtn->setFixedSize(250, 100);
    addItemBtn->setFixedSize(250, 100);
    updateItemBtn->setFixedSize(250, 100);
    deleteItemBtn->setFixedSize(250, 100);
    changeBtn->setStyleSheet("font-size: 25px;");
    quitBtn->setStyleSheet("font-size: 25px;");
    addItemBtn->setStyleSheet("font-size: 25px;");
    updateItemBtn->setStyleSheet("font-size: 25px;");
    deleteItemBtn->setStyleSheet("font-size: 25px;");
    //login->setAlignment(Qt::AlignCenter);

    /*if (this->user->GetImage() == "")
    {
        map = new QPixmap(defaultImage);
    }
    else map = new QPixmap(this->user->GetImage());

    mapSize = new QSize(300, 300);
    *map = map->scaled(*mapSize, Qt::KeepAspectRatio);
    image->setPixmap(*map);
    image->setAlignment(Qt::AlignCenter);*/
    mapSize = new QSize(300, 300);


    QPixmap mask("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\circleMask.png");
    image->setMask(mask.mask());
    //image->setAlignment(Qt::AlignCenter);

    vbox->addWidget(image);
    vbox->addWidget(login);
    hbox->addLayout(vbox);
    vboxMain->addLayout(hbox);
    vbox2->addWidget(addItemBtn);
    vbox2->addWidget(updateItemBtn);
    vbox2->addWidget(deleteItemBtn);
    vbox2->addWidget(changeBtn);
    vbox2->addWidget(quitBtn);
    hbox2->addLayout(vbox2);
    vboxMain->addStretch(0);
    vboxMain->addLayout(hbox2);

    //hbox->addLayout(vbox);
    //hbox->addLayout(vbox2);
    //vbox->addLayout(vbox2);

    this->setLayout(vboxMain);

    connect(changeBtn, SIGNAL(clicked()), SLOT(on_changeBtn_clicked()));
    connect(addItemBtn, SIGNAL(clicked()), SLOT(on_addItemBtn_clicked()));
    connect(updateItemBtn, SIGNAL(clicked()), SLOT(on_updateItemBtn_clicked()));
    connect(deleteItemBtn, SIGNAL(clicked()), SLOT(on_deleteItemBtn_clicked()));
}

void Profile::on_changeBtn_clicked()
{
    ChangeInfoDialog changeDialog(this, database);
    changeDialog.exec();

    login->setText(user->GetLogin());

    map = new QPixmap(user->GetImage());
    *map = map->scaled(*mapSize, Qt::KeepAspectRatio);
    image->setPixmap(*map);
}

void Profile::on_addItemBtn_clicked()
{
    AddItemDialog addDialog(this, catalog);
    addDialog.exec();
}

QLabel* Profile::GetImageLabel()
{
    return image;
}

QLabel* Profile::GetLoginLabel()
{
    return login;
}

void Profile::ShowABtns()
{
    addItemBtn->show();
    updateItemBtn->show();
    deleteItemBtn->show();
}

void Profile::on_updateItemBtn_clicked()
{
    UpdateItemDialog updateDialog(this, catalog);
    updateDialog.exec();
}

void Profile::on_deleteItemBtn_clicked()
{
    DeleteItemDialog deleteDialog(this, catalog);
    deleteDialog.exec();
}
