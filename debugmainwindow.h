#ifndef DEBUGMAINWINDOW_H
#define DEBUGMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class DebugMainWindow;
}

class DebugMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugMainWindow(QWidget *parent = 0);
    ~DebugMainWindow();
    int breakPoint = 0;

private slots:
    void on_debugSpinBox_editingFinished();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void beginDebug();
    void nextMove();
private:
    Ui::DebugMainWindow *ui;
};

#endif // DEBUGMAINWINDOW_H
