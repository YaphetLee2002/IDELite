#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBlock>

class ConsoleWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    ConsoleWidget(QWidget* parent=0);
    int inputDone = 0;
    QString sendData;
signals:
    void sendDataDone();
protected:
    void keyPressEvent(QKeyEvent *event)override;
protected slots:
    void resetCursorPosition();
};

#endif // CONSOLEWIDGET_H
