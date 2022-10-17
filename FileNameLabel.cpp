#include "FileNameLabel.h"

FileNameLabel::FileNameLabel(QString fileName, QLabel *parent):QLabel(parent)
{
    QFont fileFont("Microsoft YaHei", 12, 70);
    this->setText(fileName);
    this->setFont(fileFont);
    this->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
}
