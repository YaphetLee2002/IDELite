#include "functionlist.h"
#include <QRegularExpression>

FunctionList::FunctionList(QString t)
{
    text = t;
}

QStringList FunctionList::functionList(){
    QRegularExpression pattern = QRegularExpression("\\w+\\s+\\w+\\(.*\\){?(?!;)");
    QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(text);
    QStringList list;
    while(matchIterator.hasNext()){
        QRegularExpressionMatch match = matchIterator.next();
        QString s = "";
        for(int i = match.capturedStart(); i < match.capturedEnd() - 1; i++){
            s += text.at(i);
        }
        if(text.at(match.capturedEnd() - 1) != "{"){
            s += text.at(match.capturedEnd() - 1);
        }
        list.append(s);
    }
    return list;
}
