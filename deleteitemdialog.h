#ifndef DELETEITEMDIALOG_H
#define DELETEITEMDIALOG_H

#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QDialog>

class Widget;

class DeleteItemDialog : public QDialog
{
    Q_OBJECT
public:
    DeleteItemDialog(QWidget* parent = nullptr, Widget* catalog = nullptr);

private:
    Widget* catalog;

    QLabel* itemLabel;
    QRadioButton* bookType;
    QRadioButton* sbookType;
    QLabel* searchLabel;
    QRadioButton* titleSearch;
    QRadioButton* idSearch;
    QButtonGroup* itemGroup;
    QButtonGroup* searchGroup;
    QLabel* deleteLabel;
    QLineEdit* dataDelete;
    QPushButton* deleteBtn;
    QVBoxLayout* vbox;

public slots:
    void on_deleteBtn_clicked();
    void on_sbookBtn_toggled();
    void on_bookBtn_toggled();
    void on_titleSearchBtn_toggled();
    void on_idSearchBtn_toggled();
};

#endif // DELETEITEMDIALOG_H
