#include "comleter.h"
Comleter::Comleter(QWidget *parent):QListWidget(parent)
{
  p=(QPlainTextEdit*)parent;
  backgroundColor=Qt::lightGray;//.setRgb(34,39,49);
  highlightColor.setRgb(22,165,248);
  QColor color;
  QPalette palette=this->palette();
  palette.setColor(QPalette::Active,QPalette::Highlight,highlightColor);
  palette.setColor(QPalette::Inactive,QPalette::Highlight,highlightColor);
  palette.setColor(QPalette::Active, QPalette::Base,backgroundColor);
  palette.setColor(QPalette::Inactive, QPalette::Base, backgroundColor);
  color.setRgb(53,51,66);
  palette.setColor(QPalette::Text,color);
  this->setPalette(palette);
}

void Comleter::keyPressEvent(QKeyEvent *event){
  if(event->key()==Qt::Key_Up||event->key()==Qt::Key_Down){
      QListWidget::keyPressEvent(event);
    }else{
      QApplication::sendEvent(p,event);
      p->setFocus();
    }
}

int Comleter::ldistance(const std::string source, const std::string target){
  //step 1

          int n = source.length();
          int m = target.length();
          if (m == 0) return n;
          if (n == 0) return m;
          //建立一个矩阵
          typedef vector< vector<int> >  Tmatrix;
          Tmatrix matrix(n + 1);
          for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);
          //step 2 初始化
          for (int i = 1; i <= n; i++) matrix[i][0] = i;
          for (int i = 1; i <= m; i++) matrix[0][i] = i;
          //step 3
          for (int i = 1; i <= n; i++)
          {
                  const char si = source[i - 1];
                  //step 4
                  for (int j = 1; j <= m; j++)
                  {
                          const char dj = target[j - 1];
                          //step 5
                          int cost;
                          if (si == dj){
                                  cost = 0;
                          }
                          else{
                                  cost = 1;
                          }
                          //step 6
                          const int above = matrix[i - 1][j] + 1;
                          const int left = matrix[i][j - 1] + 1;
                          const int diag = matrix[i - 1][j - 1] + cost;
                          matrix[i][j] = min(above, min(left, diag));
                  }
          }//step7
          return matrix[n][m];

}

