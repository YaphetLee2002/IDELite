#ifndef FILENAMELABEL_H
#define FILENAMELABEL_H

// 文件名部件类

#include <QLabel>
#include <QFont>
#include <QDebug>

class FileNameLabel : public QLabel
{
public:
    QFont fileFont;
    explicit FileNameLabel(QString, QLabel *parent = 0);
};

#endif // FILENAMELABEL_H
