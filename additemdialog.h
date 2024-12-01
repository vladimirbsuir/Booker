#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLineEdit>

class Widget;

class AddItemDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddItemDialog(QWidget *parent = nullptr, Widget* catalog = nullptr);

private:
    Widget* catalog;

    QLabel* choiceText;
    QRadioButton* addBookBtn;
    QRadioButton* addSBookBtn;
    QPushButton* chooseItemBtn;
    QVBoxLayout* vbox;

    QLabel* desc;
    QLabel* title;
    QLabel* author;
    QLabel* image;
    QLabel* id;
    QLabel* ids;
    QLineEdit* descEdit;
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QLineEdit* idEdit;
    QLineEdit* idsEdit;
    QPushButton* chooseImageBtn;
    QPushButton* addItemBtn;
    QPushButton* backBtn;

    QString imagePath;

public slots:
    void on_chooseItemBtn_clicked();
    void on_addItemBtn_clicked();
    void on_backBtn_clicked();
    void on_chooseImageBtn_clicked();
};

#endif // ADDITEMDIALOG_H
