#include "bookpage.h"
#include "widget.h"
#include "myimagelabel.h"
#include "user.h"
#include "featured.h"
#include "menu.h"
#include "combase.h"

BookPage::BookPage(QWidget *parent, Widget* catal, User* user, Featured* featured, Combase* combase)
    : QWidget{parent}
{
    this->catal = catal;
    this->user = user;
    this->featured = featured;
    this->combase = combase;

    comments = new QVector<QLabel*>();
    //stars = new QVector<QPushButton*>();
    starsHBox = new QHBoxLayout();
    InitiateStars();

    hbox = new QHBoxLayout();
    vbox1 = new QVBoxLayout();
    //vbox1->SetFixedSize(100, 100);
    vbox2 = new QVBoxLayout();
    title = new QLabel();
    ratingLabel = new QLabel();
    ratingLabel->setAlignment(Qt::AlignHCenter);
    ratingLabel->setStyleSheet("font-size: 15px;");
    title->setStyleSheet("font-size: 15px;");
    title->setWordWrap(true);
    desc = new QLabel();
    image = new QLabel();
    btn = new QPushButton("Back");
    //btn->setFixedWidth(200);
    featureImage = new MyImageLabel(nullptr, this);
    //featureImage->setText("There should be a picture");
    connect(btn, SIGNAL(clicked()), SLOT(on_btn_clicked()));
    //vbox1->setSpacing(0);

    commentLabel = new QLabel("Your comment:");
    commentEdit = new QTextEdit();
    commentBtn = new QPushButton();
    connect(commentBtn, SIGNAL(clicked()), SLOT(on_comBtn_clicked()));
    commentLabel->setStyleSheet("font-size: 20px; color: green;");
    //commentEdit->setFixedWidth(500);
    //commentBtn->setFixedWidth(200);


    userComments = new QScrollArea();
    commentsVBox = new QVBoxLayout();
    //userComments->setLayout(commentsVBox);
    testW = new QWidget();
    testW->setLayout(commentsVBox);
    userComments->setWidget(testW);
    //userComments->setSizePolicy(QSizePolicy::Fixed);
    commentsVBox->setSizeConstraint(QLayout::SetFixedSize);
    //userComments->resize(100, 100);
    //userComments->setWidgetResizable(true);
    userComments->setMinimumHeight(100);

    vbox1->addWidget(image);
    vbox1->addWidget(title);
    vbox1->addWidget(ratingLabel);
    vbox1->addWidget(featureImage);
    vbox1->addStretch(1);
    vbox1->addWidget(btn);
    //vbox1->setSizeConstraint(QLayout::SetFixedSize);

    vbox2->addWidget(desc);
    vbox2->addStretch(1);
    vbox2->addWidget(commentLabel);
    vbox2->addWidget(commentEdit);
    vbox2->addLayout(starsHBox);
    vbox2->addWidget(commentBtn);
    vbox2->addWidget(userComments);
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

void BookPage::SetWType(int type)
{
    this->wType = type;
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

void BookPage::SetStrTitle(QString title)
{
    this->strTitle = title;
}

void BookPage::on_btn_clicked()
{
    commentBtn->show();
    commentEdit->clear();
    this->hide();

    for (int i = 0; i < comments->size(); i++) (*comments)[i]->deleteLater();
    comments->clear();

    if (wType == 1)
    {
        catal->GetArea()->show();
        menu->GetPages()->show();
        menu->GetLineEdit()->show();
        menu->GetPageBtn()->show();
    }
    else if (wType == 2)
    {
        featured->GetArea()->show();
    }
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

void BookPage::SetMenu(Menu* menu)
{
    this->menu = menu;
}

void BookPage::on_comBtn_clicked()
{
    QString comment = commentEdit->toPlainText();

    if (isComExist == 0)
    {
        combase->InsertComment(strTitle, user->GetLogin(), comment, user_rating);
        commentBtn->hide();
    }
    else
    {
        if (oldComment != comment || old_rating != user_rating)
        {
            combase->UpdateComment(strTitle, user->GetLogin(), comment, user_rating);
            QMessageBox::about(this, "Message", "Your comment was updated");
        }
        else QMessageBox::about(this, "Message", "You didn't change the comment");
    }
}

QVector<QLabel*>* BookPage::GetComments()
{
    return comments;
}

void BookPage::CommentExist(QVector<QString>* data)
{
    QString login = user->GetLogin();

    for (int i = 0; i < data->size(); i += 3)
    {
        if (login == (*data)[i])
        {
            commentBtn->setText("Change comment");
            oldComment = (*data)[i + 1];
            commentEdit->setText(oldComment);
            old_rating = (*data)[i + 2].toInt();
            isComExist = 1;
            return;
        }
    }

    commentBtn->setText("Add comment");
    isComExist = 0;
}

void BookPage::FillComments(QVector<QString>* data)
{
    if (data->size() == 0)
    {
        userComments->hide();
        ratingLabel->setText("Rating:");
        return;
    }
    else userComments->show();

    main_rating = 0;

    for (int i = 0; i < data->size(); i+=3)
    {
        QLabel* label = new QLabel();
        label->setStyleSheet("font-size: 15px;");
        label->setText((*data)[i] + ": " + (*data)[i + 1] + "\nRating: " + (*data)[i + 2]);
        main_rating += (*data)[i + 2].toInt();
        comments->append(label);
        commentsVBox->addWidget(label);
    }

    main_rating /= (data->size() / 3);
    ratingLabel->setText("Rating: " + QString::number(main_rating, 'd', 1));
}

void BookPage::InitiateStars()
{
    user_rating = 5;

    for (int i = 0; i < 5; i++)
    {
        QPixmap map("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddedToFeatured.jpg");
        QPushButton* tempBtn = new QPushButton();
        tempBtn->setStyleSheet("border: none;");
        QIcon btnIcon(map);
        tempBtn->setIcon(btnIcon);
        tempBtn->setIconSize(QSize(50,50));
        starsHBox->addWidget(tempBtn);
        stars.append(tempBtn);

        connect(tempBtn, SIGNAL(clicked()), SLOT(on_star_clicked()));
        tempBtn->setProperty("id", i);
    }
}

void BookPage::on_star_clicked()
{
    QPushButton* tempBtn = qobject_cast<QPushButton*>(sender());
    int id = tempBtn->property("id").toInt();
    user_rating = id + 1;

    for (int i = 0; i <= id; i++)
    {
        QPixmap map("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddedToFeatured.jpg");
        QIcon btnIcon(map);
        stars[i]->setIcon(btnIcon);
        stars[i]->setIconSize(QSize(50, 50));

        if (i == id)
        {
            for (int j = id + 1; j < 5; j++)
            {
                QPixmap map2("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddToFeatured.jpg");
                QIcon btnIcon2(map2);
                stars[j]->setIcon(btnIcon2);
                stars[j]->setIconSize(QSize(50, 50));
            }
        }
    }
}
