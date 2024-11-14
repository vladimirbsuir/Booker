#ifndef BOOKPAGE_H
#define BOOKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

// Добавить добавление при авторизации featured строки с индексами книг, продумать, надо ли хранить в user эту строку, как обращаться к ней
// и выводить информацию

class Widget;
class MyImageLabel;
class User;
class Featured;
class Menu;
class Combase;

class BookPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookPage(QWidget *parent = nullptr, Widget* catal = nullptr, User* user = nullptr, Featured* featured = nullptr, Combase* combase = nullptr);
    QLabel* GetTitle();
    QLabel* GetImage();
    QLabel* GetDesc();
    MyImageLabel* GetFeatureImage();
    int GetState();
    void SetIndex(int);
    void SetState(int);
    void SetWType(int);
    void ChangeFeatureImage();
    void SetMenu(Menu*);
    void SetStrTitle(QString);
    QVector<QLabel*>* GetComments();
    void FillComments(QVector<QString>*);
    void InitiateStars();
    void CommentExist(QVector<QString>*);

public slots:
    void on_btn_clicked();
    void on_star_clicked();

private:
    Widget* catal;
    User* user;
    Featured* featured;
    Menu* menu;
    Combase* combase;

    QHBoxLayout* hbox;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QScrollArea* area;
    QLabel* title;
    QLabel* ratingLabel;
    QLabel* image;
    QLabel* desc;
    QPushButton* btn;
    MyImageLabel* featureImage;
    QLabel* commentLabel;
    QTextEdit* commentEdit;
    QPushButton* commentBtn;
    QScrollArea* userComments;
    QVBoxLayout* commentsVBox;
    QString strTitle;
    QVector<QLabel*>* comments;
    QVector<QPushButton*> stars;
    QHBoxLayout* starsHBox;
    QString oldComment;
    int isComExist;
    int user_rating;
    int old_rating;
    double main_rating;
    int state;
    int index;
    int wType;

    QWidget* testW;

public:
    static QString addImagePath;
    static QString addedImagePath;

public slots:
    void on_comBtn_clicked();
};

#endif // BOOKPAGE_H
