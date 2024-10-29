#ifndef MYIMAGELABEL_H
#define MYIMAGELABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class BookPage;

class MyImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyImageLabel(QWidget *parent = nullptr, BookPage* page = nullptr);
protected:
    virtual void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    BookPage* page;
};

#endif // MYIMAGELABEL_H
