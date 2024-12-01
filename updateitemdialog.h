#ifndef UPDATEITEMDIALOG_H
#define UPDATEITEMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QTextEdit>

class Widget;

class UpdateItemDialog : public QDialog
{
    Q_OBJECT
public:
    UpdateItemDialog(QWidget* parent = nullptr, Widget* catalog = nullptr);

private:
    Widget* catalog;

    QLineEdit* titleEdit;
    QTextEdit* descEdit;
    QRadioButton* idSearch;
    QRadioButton* titleSearch;
    QButtonGroup* typeGroup;
    QButtonGroup* searchGroup;
    QLabel* searchTypeLabel;
    QLabel* titleLabel;
    QLabel* descLabel;
    QLabel* itemType;
    QPushButton* enterBtn;
    QRadioButton* bookType;
    QRadioButton* sbookType;
    QVBoxLayout* vbox;

public slots:
    void on_enterBtn_clicked();
    void on_sbookBtn_toggled();
    void on_bookBtn_toggled();
    void on_idSearchBtn_toggled();
    void on_titleSearchBtn_toggled();
};

#endif // UPDATEITEMDIALOG_H
