#ifndef IDELite_H
#define IDELite_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QFont>
#include <QAction>
#include <QPlainTextEdit>
#include <QTextCodec>
#include <QFileDialog>
#include "MoveWgt.h"
#include "DragWgt.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "ScreenButton.h"
#include "FileNameLabel.h"
#include "PlainTextEdit.h"
#include "FileList.h"
#include "HighLighter.h"
#include "StartWidget.h"
#include <QProcess>
#include <assert.h>
#include <functionlist.h>
#include "replacemainwindow.h"
#include "searchstring.h"
#include<QTimer>
#include <consolewidget.h>
#include <debugmainwindow.h>
// 主体窗口

class IDELitePrivate;

class IDELite : public QWidget {
    Q_OBJECT
    Move_Wgt
    Drag_Wgt
public:
    explicit IDELite(QWidget *parent = 0);
    ~IDELite();

    QGridLayout *lo; //阴影部分

    StartWidget *startWidget; // 初始界面
    QVBoxLayout *runRegion; //初始编辑区

    QWidget *menuWidget; //标题栏
    QString fileName;//当前文件名
    FileNameLabel * fileNameLabel; //当前文件名Label

    PlainTextEdit *plainTextEdit; //当前文本框
    QPlainTextEdit *runTextEdit; //运行消息回显
    ConsoleWidget *console; //控制台
    FileList *fileList; //当前文件列表
    MenuButton* fileButton; //文件按钮
    MainMenu* fileMenu; //文件菜单
    QAction* openFileAction;
    QAction* newFileAction;
    MenuButton* buildButton; //构建按钮
    MainMenu* buildMenu; //构建菜单
    MenuButton* themeButton; //主题按钮
    MainMenu* themeMenu; //主题菜单
    MenuButton* searchButton; // 搜索与替换按钮
    MainMenu* searchMenu; // 搜索与替换菜单
    QAction* replaceAction;

    HighLighter *highlighter; // 语法高亮类
    QProcess* cmdProcess;//新进程
    FunctionList *functionlist; //当前文件函数列表
    ReplaceMainWindow rmw; //搜索与替换界面
    DebugMainWindow dmw;//debug界面
    SearchString* search = NULL; // 搜索与替换类
    QTimer *timer; // 定时器

private:
    IDELitePrivate *d;

signals:
    void setReplaceTrue();
    void setReplaceFalse();
private slots:
    void setPurple();
    void setDark();
    void setRed();
    void setOrange();
    void setGreen();
    void setBlue();

    void maxScreen();
    void setFileName(QString);
    int on_compileAction_triggered();
    void on_runAction_triggered();
    void on_compileAndRunAction_triggered();
    void on_replaceAction_triggered();
    void on_debugAction_triggered();

    void newStart();
    void openStart();
    void setEdit();

    void on_readoutput();//标准输出槽函数
    void on_readerror();//标准错误槽函数
    void on_plainTextEdit_textChanged();
    void keyPressEvent(QKeyEvent *event) override;

    void searchLineEdit_editingFinished();
    void searchBeginPushButton_clicked();
    void previousSearchPushButton_clicked();
    void nextSearchPushButton_clicked();
    void replaceLineEdit_editingFinished();
    void replacePushButton_clicked();
    void replaceAllPushButton_clicked();
    void on_sendData();
    void on_beginDebug();
    void on_nextMove();
};

#endif // IDELite_H
