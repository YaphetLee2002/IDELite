#ifndef SCREENBUTTON_H
#define SCREENBUTTON_H

// 窗口操控按钮部件

#include <QPushButton>

class ScreenButton
{
public:
    ScreenButton();
    QPushButton* quitButton;
    QPushButton* minButton;
    QPushButton* maxButton;
};

#endif // SCREENBUTTON_H
