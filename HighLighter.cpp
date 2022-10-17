#include "Highlighter.h"

HighLighter::HighLighter(QTextDocument *parent): QSyntaxHighlighter(parent){
    HighLightingRule rule;

    // 设定关键词高亮
    keywordFormat.setForeground(keywordColor);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns; // 关键词集合，都以正则表达式表示
    keywordPatterns << "\\bauto\\b"
                    << "\\bbreak\\b"
                    << "\\bcase\\b" << "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
                    << "\\bdefault\\b" << "\\bdouble\\b" << "\\bdo\\b" << "\\bdefine\\b"
                    << "\\benum\\b" << "\\belse\\b" << "\\bextern\\b"
                    << "\\bfor\\b" << "\\bfloat\\b"
                    << "\\bgoto\\b"
                    << "\\bif\\b" << "\\binline\\b" << "\\bint\\b" << "\\binclude\\b"
                    << "\\blong\\b"
                    << "\\boperator\\b"
                    << "\\breturn\\b" << "\\bregister\\b"
                    << "\\bshort\\b" << "\\bsigned\\b" << "\\bstatic\\b" << "\\bstruct\\b" << "\\bswitch\\b" << "\\bsizeof\\b"
                    << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b"
                    << "\\bwhile\\b";

    foreach(const QString &pattern, keywordPatterns){
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // 设定操作符高亮
    operatorFormat.setForeground(operatorColor);
    rule.pattern = QRegularExpression("[,:?\\|~([])(->)\\.]");
    rule.format = operatorFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegularExpression("[+\\-*\\/&^!><=]=?");
    rule.format = operatorFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegularExpression("[(<<)(>>)(++)(--)]=?");
    rule.format = operatorFormat;
    highlightingRules.append(rule);

    // 设定数字高亮
    dataFormat.setForeground(dataColor);
    rule.pattern = QRegularExpression("[0-9]+");
    rule.format = dataFormat;
    highlightingRules.append(rule);

    // 设定单行注释高亮
    singleLineCommentFormat.setForeground(singleLineCommentColor);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    // 设定字符串高亮
    quotationFormat.setForeground(quotationColor);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // 设定函数名高亮
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(functionColor);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // 设定头文件高亮
    headerFileFormat.setForeground(headerFileColor);
    rule.pattern = QRegularExpression("<.*>");
    rule.format = headerFileFormat;
    highlightingRules.append(rule);

    // 多行注释，只设定了样式，具体匹配在highlightBlock中设置
    multiLineCommentFormat.setForeground(multiLineCommentColor);
    commentStartExpression = QRegularExpression("\\/\\*"); // 多行注释开头的匹配正则表达式
    commentEndExpression = QRegularExpression("\\*\\/"); // 多行注释结尾的匹配正则表达式
}

void HighLighter::highlightBlock(const QString &text){ // 应用高亮规则，也用于区块的高亮，比如多行注释

    //文本采用高亮规则
    foreach (const HighLightingRule &rule, highlightingRules){
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while(matchIterator.hasNext()){
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0); // 以下是多行注释的匹配

    int startIndex = 0;
    if(previousBlockState() != 1){
        startIndex = text.indexOf(commentStartExpression);
    }

    while(startIndex >= 0){
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if(endIndex == -1){
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }else{
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = (text.indexOf(commentStartExpression, startIndex + commentLength));
    }
}
