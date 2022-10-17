#include "consolewidget.h"
#include <QDebug>

ConsoleWidget::ConsoleWidget(QWidget *parent):QPlainTextEdit(parent)
{
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(resetCursorPosition()));
}

void ConsoleWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Backspace&&this->textCursor().atBlockStart()){
        return;
    }
    if(event->key()==Qt::Key_Return){
        QString data=(this->textCursor()).block().text()+tr("\n");
        sendData = data;
        emit(sendDataDone());
    }
    QPlainTextEdit::keyPressEvent(event);
}

void ConsoleWidget::resetCursorPosition(){
  QTextCursor cursor=this->textCursor();
  cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
  this->setTextCursor(cursor);
}
