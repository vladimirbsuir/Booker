#ifndef MYLABEL_H
#define MYLABEL_H

#include "mainwindow.h"

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);
    void SetIndex(int index);
    void SetWindow(MainWindow* w);
    void SetWType(int type);
protected:
    virtual void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
private:
    int index;
    int wType;
    MainWindow* w;
};

#endif // MYLABEL_H
