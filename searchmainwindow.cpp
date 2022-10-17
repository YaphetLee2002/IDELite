#include "searchmainwindow.h"
#include "ui_searchmainwindow.h"

SearchMainWindow::SearchMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchMainWindow)
{
    ui->setupUi(this);
}

SearchMainWindow::~SearchMainWindow()
{
    delete ui;
}

void SearchMainWindow::on_searchLineEdit_editingFinished()
{
    if(ui->searchLineEdit->text() != ""){
        if(parent->search != NULL){
            delete parent->search;
        }
        parent->search = new SearchString(ui->searchLineEdit->text(), parent->plainTextEdit->toPlainText());
    }
}

// 开始查询
void MainWindow::on_searchBeginPushButton_clicked()
{
    int a = search->beginSearch();
    parent->plainTextEdit->moveCursor(QTextCursor::Start);
    for(int i = 0; i < a; i++){
        parent->plainTextEdit->moveCursor(QTextCursor::Right);
    }
    parent->plainTextEdit->setFocus();
    parent->plainTextEdit->centerCursor();
}

// 上一个
void SearchMainWindow::on_previousSearchPushButton_clicked()
{

    int a = parent->search->searchPrevious();
    if(a == -1) {
        parent->plainTextEdit->setFocus();
        return;
    }
    // 将光标移动到previous
    parent->plainTextEdit->moveCursor(QTextCursor::Start);
    for(int i = 0; i < a; i++){
        parent->plainTextEdit->moveCursor(QTextCursor::Right);
    }
    parent->plainTextEdit->setFocus();
    parent->plainTextEdit->centerCursor();
}

// 下一个
void SearchMainWindow::on_nextSearchPushButton_clicked()
{
    int a = parent->search->searchNext();
    if(a == -1) {
        parent->plainTextEdit->setFocus();
        return;
    }
    // 将光标移动到next
    parent->plainTextEdit->moveCursor(QTextCursor::Start);
    for(int i = 0; i < a; i++){
        parent->plainTextEdit->moveCursor(QTextCursor::Right);
    }
    parent->plainTextEdit->setFocus();
    parent->plainTextEdit->centerCursor();
}
