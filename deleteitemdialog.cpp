#include "deleteitemdialog.h"
#include "widget.h"
#include "bookbase.h"
#include "sbookbase.h"

#include <QMessageBox>

DeleteItemDialog::DeleteItemDialog(QWidget* parent, Widget* catalog) : QDialog(parent) {
    this->catalog = catalog;

    deleteLabel = new QLabel("Enter title:");
    bookType = new QRadioButton("Book");
    sbookType = new QRadioButton("Serial book");
    titleSearch = new QRadioButton("Title");
    idSearch = new QRadioButton("ID");
    deleteBtn = new QPushButton("Delete");
    itemLabel = new QLabel("Choose item type:");
    searchLabel = new QLabel("Search by:");
    dataDelete = new QLineEdit();
    searchGroup = new QButtonGroup();
    itemGroup = new QButtonGroup();
    vbox = new QVBoxLayout();

    itemGroup->addButton(bookType);
    itemGroup->addButton(sbookType);
    searchGroup->addButton(titleSearch);
    searchGroup->addButton(idSearch);

    vbox->addWidget(itemLabel);
    vbox->addWidget(bookType);
    vbox->addWidget(sbookType);
    vbox->addWidget(searchLabel);
    vbox->addWidget(titleSearch);
    vbox->addWidget(idSearch);
    vbox->addWidget(deleteLabel);
    vbox->addWidget(dataDelete);
    vbox->addWidget(deleteBtn);

    this->setLayout(vbox);

    connect(deleteBtn, SIGNAL(clicked()), SLOT(on_deleteBtn_clicked()));
    connect(bookType, SIGNAL(clicked()), SLOT(on_bookBtn_toggled()));
    connect(sbookType, SIGNAL(clicked()), SLOT(on_sbookBtn_toggled()));
    connect(idSearch, SIGNAL(clicked()), SLOT(on_idSearchBtn_toggled()));
    connect(titleSearch, SIGNAL(clicked()), SLOT(on_titleSearchBtn_toggled()));
}

void DeleteItemDialog::on_deleteBtn_clicked()
{
    QString data = dataDelete->text();

    if (data == "")
    {
        QMessageBox::warning(this, "Warning", "Title field is empty");
        return;
    }

    bool isNum;
    int verifyNum = data.toInt(&isNum);
    if (isNum && titleSearch->isChecked())
    {
        QMessageBox::warning(this, "Warning", "Search by title using id, needed title");
        return;
    }
    else if (!isNum && idSearch->isChecked())
    {
        QMessageBox::warning(this, "Warning", "Search by id using title, needed id");
        return;
    }

    int type = 0;
    if (idSearch->isChecked()) type = 2;
    else if (titleSearch->isChecked()) type = 1;

    if (bookType->isChecked())
    {
        if (catalog->GetBookbase()->Delete(data, type))
        {
            dataDelete->clear();
            QMessageBox::about(this, "Info", "Item was successfully deleted");
        }
        else QMessageBox::warning(this, "Info", "No item to delete");
    }
    else if (sbookType->isChecked())
    {
        if (catalog->GetSBookbase()->Delete(data, type))
        {
            dataDelete->clear();
            QMessageBox::about(this, "Info", "Item was successfully deleted");
        }
        else QMessageBox::warning(this, "Info", "No item to delete");
    }
}

void DeleteItemDialog::on_bookBtn_toggled()
{
    idSearch->show();
}

void DeleteItemDialog::on_sbookBtn_toggled()
{
    idSearch->hide();
    titleSearch->setChecked(true);
    deleteLabel->setText("Enter title of the item:");
}

void DeleteItemDialog::on_idSearchBtn_toggled()
{
    deleteLabel->setText("Enter id of the item:");
}

void DeleteItemDialog::on_titleSearchBtn_toggled()
{
    deleteLabel->setText("Enter title of the item:");
}
