#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QHBoxLayout>

class StartWidget : public QWidget
{

public:
    explicit StartWidget(QWidget *parent = 0);
    QPushButton *newButton;
    QPushButton *openButton;

};

#endif // STARTWIDGET_H
