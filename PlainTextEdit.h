#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

// 编辑器部件

#include <QFont>
#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include "comleter.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class CodeLineArea;
class FunctionFoldArea;

class PlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    PlainTextEdit(QPlainTextEdit *parent = 0);

    void codeLineAreaPaintEvent(QPaintEvent *event);

    void FunctionFoldAreaPaintEvent(QPaintEvent *event);

    int codeLineAreaWidth();

    void setUpCompleteList();

    //函数折叠
    void funFold();
    //记录鼠标在函数折叠区域时的坐标
    QPoint mousePo;
    QTextBlock getMousePositionBlock(int mouseY);//获取鼠标所在block

public slots:
    void SendTextToFile();
signals:
    SendText(QString Text);//发送文本给文件保存函数
protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    QWidget *funFoldArea;
    void paintEvent(QPaintEvent *event);

private slots:
    void updateCodeLineAreaWidth(int newBlockCount);
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection>&);
    void updateCodeLineArea(const QRect &, int);
    void highlightParentheses(QList<QTextEdit::ExtraSelection>&);
    QChar charUnderCursor(int offset=0)const;
    void updateExtraSelection();
    void showCompleteWidget();
    void on_receiveFunStr(QString funcStr);
private:
    QWidget *codeLineArea;
    QStringList completeList;//储存自动填充的关键字
    Comleter *completeWidget; //临时加载匹配的关键字
    int completeState;
    int getCompleteWidgetX();
    QString getWordOfCursor();
    int countParentheses();
    bool needPaint;
};

// Code line Area & Width Definition
class CodeLineArea : public QWidget
{
public:
    CodeLineArea(PlainTextEdit *editor) : QWidget(editor) {
        codeHighlighting = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeHighlighting->codeLineAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeHighlighting->codeLineAreaPaintEvent(event);
    }

private:
    PlainTextEdit *codeHighlighting;
};
enum CompleteState{
  Ignore=0,
  Showing=1,
  Hide=2
};
class FunctionFoldArea : public QWidget
{

public:
    FunctionFoldArea(PlainTextEdit *editor) : QWidget(editor) {
        codeEditor = editor;//与edit框通信
        setMouseTracking(true);//讲mouseMoveEvent事件变为移动鼠标就触发（默认为按下左键并移动才触发）
    }

protected:
    void paintEvent(QPaintEvent *event) {//控件重画事件
        codeEditor->FunctionFoldAreaPaintEvent(event);
    }

    void leaveEvent(QEvent *event)//鼠标离开控件事件
    {
        codeEditor->mousePo.setX(-1);
        repaint();
    }

private:
    PlainTextEdit *codeEditor;
    void mousePressEvent(QMouseEvent *event);//点击鼠标事件
};
#endif // PLAINTEXTEDIT_H



