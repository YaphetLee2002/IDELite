#ifndef SEARCHSTRING_H
#define SEARCHSTRING_H
#include <QString>
#include <QVector>

class SearchString
{
public:
    SearchString(QString searchStr, const QString &t);
    int beginSearch();
    int searchPrevious();
    int searchNext();
    int cursorNow();
    QString  replaceString="";
    QString searchString="";
    int count();
    int cursorI(int i);
private:
    QVector<int> searchList;
    QString text="";
    int searchNow = 0;
};

#endif // SEARCHSTRING_H
