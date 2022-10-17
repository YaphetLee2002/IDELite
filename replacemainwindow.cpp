#include "replacemainwindow.h"
#include "ui_replacemainwindow.h"

ReplaceMainWindow::ReplaceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReplaceMainWindow)
{
    ui->setupUi(this);
}

ReplaceMainWindow::~ReplaceMainWindow()
{
    delete ui;
}


void ReplaceMainWindow::on_SearchLineEdit_editingFinished()
{
    searchLine = ui->SearchLineEdit->text();
    emit(searchLineEditFinished());
}


void ReplaceMainWindow::on_replaceLineEdit_editingFinished()
{
    replaceLine = ui->replaceLineEdit->text();
    emit(replaceLineEditFinished());
}

void ReplaceMainWindow::replaceTrue(){
    ui->replaceLineEdit->setEnabled(true);
    ui->replaceLineEdit->setFocus();
}

void ReplaceMainWindow::replaceFalse(){
    ui->replaceLineEdit->setEnabled(false);
}

void ReplaceMainWindow::on_searchBeginPushButton_clicked()
{
    emit(searchBegin());
}


void ReplaceMainWindow::on_previousSearchPushButton_clicked()
{
    emit(searchPrevious());
}

void ReplaceMainWindow::on_nextSearchPushButton_clicked()
{
    emit(searchNext());
}



void ReplaceMainWindow::on_replacePushButton_clicked()
{
    emit(replaceNow());
}

void ReplaceMainWindow::on_replaceAlPushButton_clicked()
{
    emit(replaceAll());
}
