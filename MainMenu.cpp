#include "MainMenu.h"

MainMenu::MainMenu(QMenu *parent) : QMenu(parent)
{
    QFont actionFont("Microsoft YaHei", 10, 75);
    this->setFont(actionFont);
    this->setWindowFlags(this->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}
