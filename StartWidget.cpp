#include "StartWidget.h"

StartWidget::StartWidget(QWidget * parent) : QWidget(parent)
{
    QFont startWidgetFont("Microsoft YaHei", 12, 75);

    this->newButton = new QPushButton();
    this->openButton = new QPushButton();

    newButton->setText("New");
    openButton->setText("Open");

    newButton->setFont(startWidgetFont);
    openButton->setFont(startWidgetFont);

    newButton->setFixedSize(300, 100);
    openButton->setFixedSize(300, 100);


    QHBoxLayout *startWidgetLayout = new QHBoxLayout();
    startWidgetLayout->addWidget(newButton);
    startWidgetLayout->addWidget(openButton);
    startWidgetLayout->setStretch(0, 1);
    startWidgetLayout->setStretch(1, 1);


    this->setLayout(startWidgetLayout);

}
