#ifndef SEARCHMAINWINDOW_H
#define SEARCHMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SearchMainWindow;
}

class SearchMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchMainWindow(QWidget *parent = 0);
    ~SearchMainWindow();

private:
    Ui::SearchMainWindow *ui;
};

#endif // SEARCHMAINWINDOW_H
