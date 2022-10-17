#ifndef MENUBUTTON_H
#define MENUBUTTON_H

// 菜单标题栏按钮部件

#include <QWidget>
#include <QPushButton>
#include <QFont>

class MenuButton : public QPushButton
{
private:
    QFont menuFont;
public:
    explicit MenuButton(QString, QPushButton *parent = 0);
};

#endif // MENUBUTTON_H
