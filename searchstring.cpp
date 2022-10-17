#include "searchstring.h"
#include <QRegularExpression>
#include <QDebug>

SearchString::SearchString(QString searchStr, const QString &t)
{
    searchString = searchStr;
    text = t;
}

int SearchString::beginSearch(){
    QRegularExpression pattern = QRegularExpression(searchString);
    QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(text);
    while(matchIterator.hasNext()){
        QRegularExpressionMatch match = matchIterator.next();
        searchList.append(match.capturedStart());
    }
    if(searchList.count() >= 1){
        return searchList.at(0);
    }else{
        return -1;
    }
}

int SearchString::searchPrevious(){
    if(searchNow == 0){
        return -1;
    }else{
        int res = searchList.at(--searchNow);
        qDebug() << res;
        return res;
    }
}

int SearchString::searchNext(){
    if(searchNow == searchList.count() - 1){
        return -1;
    }else{
        int res = searchList.at(++searchNow);
        qDebug() << res;
        return res;
    }
}

int SearchString::cursorNow(){
    if(searchList.count() == 0){
        return -1;
    }
    return searchList.at(searchNow);
}

int SearchString::count(){
    return searchList.count();
}

int SearchString::cursorI(int i){
    if(i < 0 || i >= searchList.count()){
        return -1;
    }
    return searchList.at(i);
}
