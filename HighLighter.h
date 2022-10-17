#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class HighLighter : public QSyntaxHighlighter // 继承QSyntaxHighLighter
{
    Q_OBJECT

public:
    HighLighter(QTextDocument *parent = 0); // 构造函数传一个QTextDocument对象 给父类

protected:
    void highlightBlock(const QString &text) override; // 重写父类这个函数，自动调用

private :
    struct HighLightingRule{
        QRegularExpression pattern;
        QTextCharFormat format;
    }; // 语法规则结构体，包含正则表达式模式串和匹配的样式
    QVector<HighLightingRule> highlightingRules; // 规则的集合，可以定义多个高亮规则

    QRegularExpression commentStartExpression; // 注释的高亮，使用highlightBlock()匹配
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat; // 高亮样式，关键词
    QTextCharFormat singleLineCommentFormat; // 高亮样式，单行注释
    QTextCharFormat multiLineCommentFormat; // 高亮样式，多行注释
    QTextCharFormat quotationFormat; // 高亮样式，字符串
    QTextCharFormat functionFormat; // 高亮样式，函数
    QTextCharFormat headerFileFormat; // 高亮样式，引用头文件
    QTextCharFormat operatorFormat; // 高亮样式，操作符
    QTextCharFormat dataFormat; // 高亮样式，数字

    QColor keywordColor = QColor(147, 115, 238); // 关键字颜色
    QColor singleLineCommentColor = QColor(Qt::darkGray); // 单行注释颜色
    QColor multiLineCommentColor = QColor(Qt::darkGray); // 多行注释颜色
    QColor quotationColor = QColor(Qt::darkGreen); // 字符串颜色
    QColor functionColor = QColor(Qt::blue); // 函数颜色
    QColor headerFileColor = QColor(Qt::darkGreen); // 头文件颜色
    QColor operatorColor = QColor(Qt::darkRed); // 操作符颜色
    QColor dataColor = QColor(Qt::darkYellow); // 数字颜色

};

#endif // HIGHLIGHTER_H
