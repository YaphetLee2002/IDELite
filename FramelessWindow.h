#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

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
#include <QTextCodec>   // 字符编码转换头文件
#include <QFileDialog>  // 文件对话框
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
// 主体窗口

class FramelessWindowPrivate;

class FramelessWindow : public QWidget {
    Q_OBJECT
    Move_Wgt
    Drag_Wgt

public:
    explicit FramelessWindow(QWidget *parent = 0);
    ~FramelessWindow();

    QGridLayout *lo; //阴影部分

    StartWidget *startWidget; // 初始界面
    QVBoxLayout *runRegion; //初始编辑区

    QWidget *menuWidget; //标题栏
    QString fileName;//当前文件名
    FileNameLabel * fileNameLabel; //当前文件名Label

    PlainTextEdit *plainTextEdit; //当前文本框
    QPlainTextEdit *runTextEdit; //运行消息回显
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
    QAction* searchAction;
    QAction* replaceAction;

    HighLighter *highlighter; // 语法高亮类
    QProcess* cmdProcess;//新进程
    int compilerFlag = 1;//编译成功标识
    FunctionList * functionlist;
    ReplaceMainWindow rmw;
    SearchString* search = NULL;
    QTimer *timer;

private:
    FramelessWindowPrivate *d;

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
    void on_compileAction_triggered();
    void on_runAction_triggered();
    void on_replaceAction_triggered();

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
};

#endif // FRAMELESSWINDOW_H
