#ifndef FUNCTIONLIST_H
#define FUNCTIONLIST_H
#include <QStringList>

class FunctionList
{
public:
    FunctionList(QString t);
    QStringList functionList();
private:
    QString text;
};

#endif // FUNCTIONLIST_H
