#include "FramelessWindow.h"

#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDesktopWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int width = QApplication::desktop()->width();
    int height = QApplication::desktop()->height();

    // 创建窗口
    FramelessWindow *window = new FramelessWindow();
    window->resize(width / 3 * 2, height / 3 * 2);
    window->show();

    return app.exec();
}
