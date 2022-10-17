#ifndef REPLACEMAINWINDOW_H
#define REPLACEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReplaceMainWindow;
}

class ReplaceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReplaceMainWindow(QWidget *parent = 0);
    ~ReplaceMainWindow();
    QString searchLine="";
    QString replaceLine="";

public:
    Ui::ReplaceMainWindow *ui;

signals:
    void searchBegin();
    void searchPrevious();
    void searchNext();
    void replaceNow();
    void replaceAll();
    void searchLineEditFinished();
    void replaceLineEditFinished();
private slots:
    void on_SearchLineEdit_editingFinished();
    void on_replaceLineEdit_editingFinished();
    void replaceTrue();
    void replaceFalse();
    void on_searchBeginPushButton_clicked();
    void on_previousSearchPushButton_clicked();
    void on_nextSearchPushButton_clicked();
    void on_replacePushButton_clicked();
    void on_replaceAlPushButton_clicked();
};

#endif // REPLACEMAINWINDOW_H
