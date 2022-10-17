#include "debugmainwindow.h"
#include "ui_debugmainwindow.h"

DebugMainWindow::DebugMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugMainWindow)
{
    ui->setupUi(this);
}

DebugMainWindow::~DebugMainWindow()
{
    delete ui;
}

void DebugMainWindow::on_debugSpinBox_editingFinished()
{
    breakPoint = ui->debugSpinBox->value();
}

void DebugMainWindow::on_pushButton_clicked()
{
    emit(beginDebug());
}


void DebugMainWindow::on_pushButton_2_clicked()
{
    emit(nextMove());
}
