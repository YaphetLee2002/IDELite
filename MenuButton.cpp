#include "MenuButton.h"

MenuButton::MenuButton(QString buttonName, QPushButton *parent) : QPushButton(parent)
{
    QFont menuFont("Microsoft YaHei", 12, 75);
    this->setFixedSize(150, 50);
    this->setText(buttonName);
    this->setFont(menuFont);
}
