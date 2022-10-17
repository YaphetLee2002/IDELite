#ifndef FILELIST_H
#define FILELIST_H

// 文件列表部件类

#include <QTreeWidget>
#include <QScrollBar>
#include <QFont>
#include <QPainter>
// class FileList : public QListWidget
class FileList : public QTreeWidget
{
    Q_OBJECT
public:
    explicit FileList(QTreeWidget *parent = 0);
    QString currentFile;//当前文件
    bool textFlag=false;
    bool newStartFile();
    bool openStartFile();

private:
    QMap<QString,QTreeWidgetItem*> files;//决定路径和文件名
    QMap<QString,QTreeWidgetItem*> dirs;//路径和目录名
    QMap<QString,QTreeWidgetItem*> functions;//函数名
    QString shownName;//所展示文件名
    QString curPlainText;//当前编辑区文本
    bool curIsModified;//编辑区是否修改过
    bool MaybeSave();//可能需要保存文件
    bool loadFile(const QString &filename);//加载文件
    void setCurrentFile(const QString &filename);//重置当前文件

signals:
    LoadData(QString Data);//从文件中获取的内容
    ClearText();//清屏
    GetText();//保存文件时向编辑区获取文本
    SetTitle(QString name);
    setedit();
    Sendfunstr(QString fun);
    showFun();
public slots:
    bool Save();
    bool NewFile();
    bool OpenFile();
    bool SaveFile(const QString &filename);
    bool SaveAs();
    void Close();
    void OnFileChanged(QTreeWidgetItem* Item,int colum);
    void SetCurrentFilemodified();//重置编辑区修改
    void GetPlainText(QString Text);//从编辑区获取文本
    bool OpenDirectory();
    void ShowPath(QTreeWidgetItem *item, int column);
    void DoubleClickedItem(QTreeWidgetItem* Item,int column);
    void OnDispalyFun(QStringList funs);
};

#endif // FILELIST_H
