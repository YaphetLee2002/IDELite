#ifndef COMLETER_H
#define COMLETER_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QApplication>
#include <vector>
#include <string>
#include <cmath>
using std::string;
using std::vector;
using std::min;
class Comleter : public QListWidget
{
public:
    Comleter(QWidget *parent=0);
    static int ldistance(const std::string source, const std::string target);
protected:
  void keyPressEvent(QKeyEvent *event) override;
private:
  QPlainTextEdit* p;
  QColor backgroundColor;
  QColor highlightColor;

};

#endif // COMLETER_H
