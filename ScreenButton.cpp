#include "ScreenButton.h"

ScreenButton::ScreenButton()
{
    quitButton = new QPushButton();
    quitButton->setFixedSize(30, 30);

    quitButton->setStyleSheet("QPushButton{background-color: rgb(239, 83, 80); border-radius: 15px; border: none;}"
                              "QPushButton:hover{background-color: rgb(229, 57, 53)}"
                              "QPushButton:pressed{background-color: rgb(211, 47, 47)}");

    minButton = new QPushButton();
    minButton->setFixedSize(30, 30);

    minButton->setStyleSheet("QPushButton{background-color: rgb(255, 202, 40); border-radius: 15px; border: none;}"
                             "QPushButton:hover{background-color: rgb(255, 179, 0)}"
                             "QPushButton:pressed{background-color: rgb(255, 160, 0)}");

    maxButton = new QPushButton();
    maxButton->setFixedSize(30, 30);

    maxButton->setStyleSheet("QPushButton{background-color: rgb(102, 187, 106); border-radius: 15px; border: none;}"
                             "QPushButton:hover{background-color: rgb(67, 160, 71)}"
                             "QPushButton:pressed{background-color: rgb(56, 142, 60)}");
}
