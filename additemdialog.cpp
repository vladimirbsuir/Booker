#include "additemdialog.h"
#include "serialbook.h"
#include "book.h"
#include "widget.h"
#include "sbookbase.h"
#include "bookbase.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>

AddItemDialog::AddItemDialog(QWidget* parent, Widget* catalog) : QDialog(parent) {
    this->catalog = catalog;

    addBookBtn = new QRadioButton("Book", this);
    addSBookBtn = new QRadioButton("Serial Book", this);
    choiceText = new QLabel("Choose type of the item:");
    chooseItemBtn = new QPushButton("Choose");
    desc = new QLabel("Enter description");
    title = new QLabel("Enter title");
    author = new QLabel("Enter author");
    image = new QLabel("Choose image");
    id = new QLabel("Enter book id");
    ids = new QLabel("Enter books ids");
    descEdit = new QLineEdit();
    titleEdit = new QLineEdit();
    authorEdit = new QLineEdit();
    idEdit = new QLineEdit();
    idsEdit = new QLineEdit();
    chooseImageBtn = new QPushButton("Image");
    addItemBtn = new QPushButton("Add item");
    backBtn = new QPushButton("Back");
    vbox = new QVBoxLayout();

    vbox->addWidget(choiceText);
    vbox->addWidget(addBookBtn);
    vbox->addWidget(addSBookBtn);
    vbox->addWidget(chooseItemBtn);

    vbox->addWidget(title);
    vbox->addWidget(titleEdit);
    vbox->addWidget(desc);
    vbox->addWidget(descEdit);
    vbox->addWidget(author);
    vbox->addWidget(authorEdit);
    vbox->addWidget(image);
    vbox->addWidget(chooseImageBtn);
    vbox->addWidget(id);
    vbox->addWidget(idEdit);
    vbox->addWidget(ids);
    vbox->addWidget(idsEdit);
    vbox->addWidget(addItemBtn);
    vbox->addWidget(backBtn);

    title->hide();
    titleEdit->hide();
    desc->hide();
    descEdit->hide();
    image->hide();
    chooseImageBtn->hide();
    author->hide();
    authorEdit->hide();
    id->hide();
    idEdit->hide();
    ids->hide();
    idsEdit->hide();
    addItemBtn->hide();
    backBtn->hide();

    this->setLayout(vbox);

    connect(chooseItemBtn, SIGNAL(clicked()), SLOT(on_chooseItemBtn_clicked()));
    connect(backBtn, SIGNAL(clicked()), SLOT(on_backBtn_clicked()));
    connect(chooseImageBtn, SIGNAL(clicked()), SLOT(on_chooseImageBtn_clicked()));
    connect(addItemBtn, SIGNAL(clicked()), SLOT(on_addItemBtn_clicked()));

    /*QShortcut* addItemBtnSC = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    addItemBtnSC->setContext(Qt::WidgetWithChildrenShortcut);
    connect(addItemBtnSC, SIGNAL(activated()), SLOT(on_addItemBtn_clicked()));*/
}

void AddItemDialog::on_backBtn_clicked()
{
    addBookBtn->show();
    addSBookBtn->show();
    choiceText->show();
    chooseItemBtn->show();

    title->hide();
    titleEdit->hide();
    titleEdit->clear();
    desc->hide();
    descEdit->hide();
    descEdit->clear();
    image->hide();
    chooseImageBtn->hide();
    author->hide();
    authorEdit->hide();
    authorEdit->clear();
    id->hide();
    idEdit->hide();
    idEdit->clear();
    addItemBtn->hide();

    if (addSBookBtn->isChecked())
    {
        ids->hide();
        idsEdit->hide();
        idsEdit->clear();
    }

    backBtn->hide();
}

void AddItemDialog::on_chooseItemBtn_clicked()
{
    addBookBtn->hide();
    addSBookBtn->hide();
    choiceText->hide();
    chooseItemBtn->hide();

    title->show();
    titleEdit->show();
    desc->show();
    descEdit->show();
    image->show();
    chooseImageBtn->show();
    author->show();
    authorEdit->show();
    id->show();
    idEdit->show();
    addItemBtn->show();

    if (addSBookBtn->isChecked())
    {
        ids->show();
        idsEdit->show();
    }

    backBtn->show();
}

void AddItemDialog::on_chooseImageBtn_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this, "Choose image", "C://", "jpeg (*.jpg);; png (*.png);");
}

void AddItemDialog::on_addItemBtn_clicked()
{
    qDebug() << "Add item btn";

    if (titleEdit->text() == "" || descEdit->text() == "" || authorEdit->text() == "" || idEdit->text() == "")
    {
        QMessageBox::warning(this, "Warning", "Not all fields are filled");
    }

    QVector<Item*>* items = new QVector<Item*>();

    if (addSBookBtn->isChecked())
    {
        items->append(new SerialBook(6));

        (*items)[0]->GetValues()[5] = idsEdit->text();
    }
    else if (addBookBtn->isChecked()) items->append(new Book(5));

    (*items)[0]->GetValues()[0] = imagePath;
    (*items)[0]->GetValues()[1] = descEdit->text();
    (*items)[0]->GetValues()[2] = titleEdit->text();
    (*items)[0]->GetValues()[3] = authorEdit->text();
    (*items)[0]->GetValues()[4] = idEdit->text();

    if (addSBookBtn->isChecked()) catalog->GetSBookbase()->Write(items, 1, 1);
    else if (addBookBtn->isChecked()) catalog->GetBookbase()->Write(items, 1, 1);

    QMessageBox::about(this, "Info", "Item was successfully added");
}
