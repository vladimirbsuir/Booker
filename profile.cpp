#include "profile.h"
#include "changeinfodialog.h"
#include "user.h"

Profile::Profile(QWidget *parent, Database* database, User* user)
    : QWidget{parent}
{
    this->database = database;
    this->user = user;

    vbox = new QVBoxLayout();
    image = new QLabel();
    login = new QLabel();
    changeBtn = new QPushButton("Change your info");
    quitBtn = new QPushButton("Quit from account");

    login->setStyleSheet("font-size: 50px");
    login->setAlignment(Qt::AlignCenter);

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
    vbox->addStretch(0);
    vbox->addWidget(changeBtn);
    vbox->addWidget(quitBtn);

    this->setLayout(vbox);

    connect(changeBtn, SIGNAL(clicked()), SLOT(on_changeBtn_clicked()));
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

QLabel* Profile::GetImageLabel()
{
    return image;
}

QLabel* Profile::GetLoginLabel()
{
    return login;
}
