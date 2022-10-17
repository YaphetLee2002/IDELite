#include "PlainTextEdit.h"
#include<QDebug>
static QVector<QPair<QString, QString>> parentheses = {
    {"(", ")"},
    {"{", "}"},
    {"[", "]"},
    {"\"", "\""},
    {"'", "'"}
};
PlainTextEdit::PlainTextEdit(QPlainTextEdit *parent) : QPlainTextEdit(parent)
{
    QFont codeFont("Consolas", 12, 2);
    this->setFont(codeFont);
    this->setLineWrapMode(LineWrapMode::NoWrap);

    codeLineArea = new CodeLineArea(this);
    funFoldArea = new FunctionFoldArea(this);

    connect(this, SIGNAL(updateRequest(QRect,int)), funFoldArea, SLOT(update()));
    connect(this, SIGNAL(textChanged()), funFoldArea, SLOT(repaint()));

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateCodeLineAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateCodeLineArea(QRect,int)));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(updateExtraSelection()));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(showCompleteWidget()));
    updateCodeLineAreaWidth(0);
    updateExtraSelection();

    //初始化鼠标在函数折叠区域上的位置
    mousePo.setX(0);
    mousePo.setY(0);
    needPaint=false;

    //初始化代码补全菜单信息
    setUpCompleteList();
    completeWidget= new Comleter(this);
    completeWidget->hide();
    completeWidget->setMaximumHeight(fontMetrics().height()*5);
    completeState=CompleteState::Hide;

}
void PlainTextEdit::SendTextToFile(){//编辑发送文本内容至文件
    QString Text=this->toPlainText();
    emit(SendText(Text));
}

// codeLineAreaWidth Constructor
int PlainTextEdit::codeLineAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}


void PlainTextEdit::updateCodeLineAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(codeLineAreaWidth()+20, 0, 0, 0);

}


void PlainTextEdit::updateCodeLineArea(const QRect &rect, int dy)
{
    if (dy)
        codeLineArea->scroll(0, dy);
    else
        codeLineArea->update(0, rect.y(), codeLineArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateCodeLineAreaWidth(0);
}


void PlainTextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    codeLineArea->setGeometry(QRect(cr.left(), cr.top(), codeLineAreaWidth(), cr.height()));
    funFoldArea->setGeometry(QRect(cr.left()+codeLineAreaWidth(), cr.top(), 20, cr.height()));
}

// resizeEvent
// cursorPositionChanged
void PlainTextEdit::highlightCurrentLine(QList<QTextEdit::ExtraSelection>& extraSelections)
{
    //QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection{};

        QColor lightPurple;
        lightPurple.setRgb(200, 200, 200);

        selection.format.setBackground(lightPurple);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

   // setExtraSelections(extraSelections);
}


void PlainTextEdit::codeLineAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(codeLineArea);
    QColor lightPurple;
    lightPurple.setRgb(200, 200, 200);
    QColor purple;
    purple.setRgb(93, 93, 94);
    painter.fillRect(event->rect(), lightPurple);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setFont(QFont("Consolas"));
            painter.setPen(purple);
            painter.drawText(0, top, codeLineArea->width(), fontMetrics().height(),
                             Qt::AlignCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }

}

void PlainTextEdit::updateExtraSelection()
{
    QList<QTextEdit::ExtraSelection> extra;
    highlightCurrentLine(extra);
    highlightParentheses(extra);
    setExtraSelections(extra);
}

void PlainTextEdit::highlightParentheses(QList<QTextEdit::ExtraSelection>& extraSelection)
{
    auto currentSymbol = charUnderCursor();
    auto prevSymbol = charUnderCursor(-1);
   // QList<QTextEdit::ExtraSelection> extraSelection;

    for (auto& pair : parentheses)
    {
        int direction;

        QChar counterSymbol;
        QChar activeSymbol;
        auto position = textCursor().position();

        if (pair.first == currentSymbol)
        {
            direction = 1;
            counterSymbol = pair.second[0];
            activeSymbol = currentSymbol;
        }
        else if (pair.second == prevSymbol)
        {
            direction = -1;
            counterSymbol = pair.first[0];
            activeSymbol = prevSymbol;
            position--;
        }
        else
        {
            continue;
        }

        auto counter = 1;

        while (counter != 0 &&
               position > 0 &&
               position < (document()->characterCount() - 1))
        {
            //qDebug()<<position<<document()->characterCount();
            // Moving position
            position += direction;

            auto character = document()->characterAt(position);
            // Checking symbol under position
            if (character == activeSymbol)
            {
                ++counter;
            }
            else if (character == counterSymbol)
            {
                --counter;
            }
        }

        QColor color; color.setRgb(240,161,168);

        // Found
        if (counter == 0)
        {
            QTextEdit::ExtraSelection selection{};

            auto directionEnum =
                 direction < 0 ?
                 QTextCursor::MoveOperation::Left
                 :
                 QTextCursor::MoveOperation::Right;
            selection.format.setFontWeight(5);
            selection.format.setBackground(color);
            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            selection.cursor.movePosition(
                directionEnum,
                QTextCursor::MoveMode::MoveAnchor,
                std::abs(textCursor().position() - position)
            );

            selection.cursor.movePosition(
                QTextCursor::MoveOperation::Right,
                QTextCursor::MoveMode::KeepAnchor,
                1
            );

            extraSelection.append(selection);

            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            selection.cursor.movePosition(
                directionEnum,
                QTextCursor::MoveMode::KeepAnchor,
                1
            );

            extraSelection.append(selection);
        }

        break;
    }
    //setExtraSelections(extraSelection);
}

int PlainTextEdit::countParentheses()
{
   // auto position = textCursor().position();
    auto position = 1;
    auto counter = 0;
    while( position > 0 && position < (document()->characterCount() - 1)){
        position += 1;
        auto character = document()->characterAt(position);
        if(character == '{')
            ++counter;
        else if(character == '}')
            --counter;
    }
    return counter;
}

QChar PlainTextEdit::charUnderCursor(int offset) const
{
    auto block = textCursor().blockNumber();
    auto index = textCursor().positionInBlock();
    auto text = document()->findBlockByNumber(block).text();

    index += offset;

    if (index < 0 || index >= text.size())
    {
        return {};
    }

    return text[index];
}

void PlainTextEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers()==Qt::ShiftModifier&&event->key()==Qt::Key_ParenLeft){
        this->insertPlainText(tr("()"));
        this->moveCursor(QTextCursor::PreviousCharacter);
      }else if(event->key()==Qt::Key_Up&&completeState==CompleteState::Showing){
        if(completeWidget->currentRow()>0)
          completeWidget->setCurrentRow(completeWidget->currentRow()-1);
      }
    else if(event->key()==Qt::Key_Down&&(completeState==CompleteState::Showing)){
        if(completeWidget->currentRow()<completeWidget->count()-1)
          completeWidget->setCurrentRow(completeWidget->currentRow()+1);
      }
    else if(event->key()==Qt::Key_Return&&(completeState==CompleteState::Showing)){
        QString insertText=completeWidget->currentItem()->text();
        QString word=this->getWordOfCursor();
        completeState=CompleteState::Ignore;
        for(int i=0;i<word.count();++i)
          this->textCursor().deletePreviousChar();
        this->insertPlainText(insertText);
        if(insertText.contains(tr("#include")))
          this->moveCursor(QTextCursor::PreviousCharacter);  //包含头文件，将光标移至“”或<>中间
        completeState=CompleteState::Hide;
        completeWidget->hide();
      }
    else if(event->key()==Qt::Key_Return){//回车下行层级自动缩进功能
        //获得本行的文本
        QString temp=this->document()->findBlockByLineNumber(this->textCursor().blockNumber()).text();
        QPlainTextEdit::keyPressEvent(event);
        if(temp.count()<=0)return;
        //输出回车那一行的前距
        foreach(const QChar &c,temp){
            if(c.isSpace())this->insertPlainText(c);
            else break;
          }
        //如果是for() while() switch() if()则缩进一个tab,一种粗略地做法可能会出错
        if(temp.at(temp.count()-1)==')'&&(temp.contains(tr("for("))||temp.contains(tr("while("))
                                          ||temp.contains(tr("switch("))||temp.contains(tr("if("))))
            this->insertPlainText(tr("\t"));
        //如果是{ 则缩进并补}
        int c = countParentheses();
        if(temp.at(temp.count()-1)=='{' && c != 0){
            this->insertPlainText(tr("\t"));
            QTextCursor cursor=this->textCursor();
            int pos=this->textCursor().position();
            this->insertPlainText(tr("\n"));
            foreach(const QChar &c,temp){
                if(c.isSpace())this->insertPlainText(c);
                else break;
              }
            this->insertPlainText(tr("}"));
            cursor.setPosition(pos);
            this->setTextCursor(cursor);//返回中间一行
          }
        else if(temp.at(temp.count()-1) == '{'){
            this->insertPlainText(tr("\t"));
        }
      }//*/
    else if(event->key()==Qt::Key_Backspace){
        switch(this->document()->characterAt(this->textCursor().position()-1).toLatin1()){
          case '(':
            QPlainTextEdit::keyPressEvent(event);
            if(this->document()->characterAt(this->textCursor().position())==')'){
                this->textCursor().deleteChar();
              }break;
          case '\"':
            QPlainTextEdit::keyPressEvent(event);
            if(this->document()->characterAt(this->textCursor().position())=='\"'){
                this->textCursor().deleteChar();
              }break;
          case '<':
            QPlainTextEdit::keyPressEvent(event);
            if(this->document()->characterAt(this->textCursor().position())=='>'){
                this->textCursor().deleteChar();
              }break;
          default:
            QPlainTextEdit::keyPressEvent(event);
          }
      }
    else{
      QPlainTextEdit::keyPressEvent(event);
      }
}

void PlainTextEdit::setUpCompleteList(){
  completeList<< "char" << "class" << "const" << "cin" << "cout"
              << "double" << "enum" << "explicit"
              << "friend" << "inline" << "int"
              << "long" << "namespace" << "operator"
              << "private" << "protected" << "public"
              << "short" << "signals" << "signed"
              << "slots" << "static" << "struct"
              << "template" << "typedef" << "typename"
              << "union" << "unsigned" << "virtual"
              << "void" << "volatile" << "bool"<<"using"<<"constexpr"
              <<"sizeof"<<"if"<<"for"<<"foreach"<<"while"<<"do"<<"case"
              <<"break"<<"continue"<<"template"<<"delete"<<"new"
              <<"default"<<"try"<<"return"<<"throw"<<"catch"<<"goto"<<"else"
              <<"extren"<<"this"<<"switch"<<"#include <>"<<"#include \"\""<<"#define"<<"iostream"
              <<"std";
}

QString PlainTextEdit::getWordOfCursor(){
  int pos=this->textCursor().position()-1;
  QVector<QChar> words;
  QString result;
  QChar ch=this->document()->characterAt(pos+1);
  if(ch.isDigit()||ch.isLetter()||ch==' ')return result;
  ch=this->document()->characterAt(pos);
  if(ch==' ')return result;
  while(ch.isDigit()||ch.isLetter()||ch=='_'||ch=='#'){
      words.append(ch);
      pos--;
      ch=this->document()->characterAt(pos);
    }
  for(int i=words.size()-1;i>=0;i--)
    result+=words[i];
  return result;
}

void PlainTextEdit::showCompleteWidget(){
  if(completeState==CompleteState::Ignore)return;//忽略光标和文本变化的响应,避免陷入事件死循环和互相钳制
  completeWidget->hide();
  completeState=CompleteState::Hide;
  QString word=this->getWordOfCursor();
  completeWidget->clear();
  if(!word.isEmpty()){//光标所在单词是不是合法(能不能联想)
      int maxSize=0;
      QMap<QString,int> distance;
      vector<QString> itemList;
      foreach(const QString &temp,completeList){
          if(temp.contains(word)){
              itemList.push_back(temp);
              distance[temp]=Comleter::ldistance(temp.toStdString(),word.toStdString());
              if(temp.length()>maxSize)maxSize=temp.length();
            }
        }
      //有没有匹配的字符
      if(itemList.size()>0){//如果有的话
          //按单词长短，自上而下升序排列
      sort(itemList.begin(),itemList.end(),[&](const QString &s1,const QString &s2)->bool{return distance[s1]<distance[s2]; });
      foreach(const QString& item,itemList){
          completeWidget->addItem(new QListWidgetItem(item));
        }

      int x=this->getCompleteWidgetX();
      int y=this->cursorRect().y()+fontMetrics().height()*7/4;

      completeWidget->move(x,y);
      if(completeWidget->count()>5)completeWidget->setFixedHeight(fontMetrics().height()*6);
      else completeWidget->setFixedHeight(fontMetrics().height()*(completeWidget->count()+1));
      completeWidget->setFixedWidth((fontMetrics().width(QLatin1Char('9'))+6)*maxSize);
      completeWidget->show();
      completeState=CompleteState::Showing;
      completeWidget->setCurrentRow(0,QItemSelectionModel::Select);
        }
    }
  completeWidget->setStyleSheet("QScrollBar{width:10px}");

}
//completewidget的横坐标在 被匹配单词的起始处
//求出listwidget的横坐标
int PlainTextEdit::getCompleteWidgetX(){
  QTextCursor cursor=this->textCursor();
  int pos=cursor.position()-1;
  int origianlPos=pos+1;
  QChar ch;
  ch=this->document()->characterAt(pos);
  while((ch.isDigit()||ch.isLetter()||ch=='_'||ch=='#')&&pos>0){
      pos--;
      ch=this->document()->characterAt(pos);
    }
  pos++;
  completeState=CompleteState::Ignore;
  cursor.setPosition(pos);
  this->setTextCursor(cursor);
  int x=this->cursorRect().x()+2*fontMetrics().width(QLatin1Char('9'));
  cursor.setPosition(origianlPos);
  this->setTextCursor(cursor);
  completeState=CompleteState::Hide;
  return x;
}

void PlainTextEdit::on_receiveFunStr(QString funcStr){
    this->moveCursor(QTextCursor::Start);
    qDebug() << funcStr;
    if(!this->find(funcStr+"{")){
        this->find(funcStr+";");
        this->find(funcStr);
    }

    this->setFocus();
    this->centerCursor();
}
void PlainTextEdit::funFold()
{
    codeLineArea->repaint();
}
QTextBlock PlainTextEdit::getMousePositionBlock(int mouseY)
{
    QTextBlock block;
    block = firstVisibleBlock();
    while(block.blockNumber() != -1 && block.isVisible() == false)
    {
        block = block.next();
    }
    if(block.blockNumber() == -1) return block;
    int blockHeight = (int)blockBoundingRect(block).height();
    int blockNum = mouseY/blockHeight+1;

    if(blockNum <= blockCount())
    {
        for(int i = 1 ; i < blockNum ; i++)
        {
            if(block.blockNumber() == -1) return block;
            if(block.isVisible() == false) i--;
            block = block.next();
        }
        while(block.blockNumber() != -1 && block.isVisible() == false)
        {
            block = block.next();
        }
        return block;
    }
    else return block;
}
void PlainTextEdit::FunctionFoldAreaPaintEvent(QPaintEvent *event)
{
    //定义行数折叠区域的painter
    QPainter painter(funFoldArea);

    QTextBlock block = firstVisibleBlock();
    //QString temp=this->document()->findBlockByLineNumber(this->textCursor().blockNumber()).text();
    while(block.isValid())
       {
        //如果该块中有”{“，则在函数折叠区域画倒三角
        if(block.text().indexOf('{') != -1)
        {
            int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
           // int bottom = top + (int) blockBoundingRect(block).height();
            painter.setPen(Qt::blue );
            if(!block.next().isVisible())
            {
                //设置小三角的规则
                QPointF points[3] = {
                    QPointF(12,top+5),
                    QPointF(6,top+11),
                    QPointF(12,top+11)
                };
                painter.drawPolygon(points,3);
                QPointF points1[3] = {
                    QPointF(11,top+6),
                    QPointF(7,top+10),
                    QPointF(11,top+10)
                };
                painter.drawPolygon(points1,3);
                QPointF points2[3] = {
                    QPointF(10,top+7),
                    QPointF(8,top+9),
                    QPointF(10,top+9)
                };
                painter.drawPolygon(points2,3);
            }
            else
            {
                QPointF points[3] = {
                    QPointF(12,top+5),
                    QPointF(6,top+11),
                    QPointF(12,top+11)
                };
                painter.drawPolygon(points,3);
            }

        }
            block = block.next();
        }
}
void FunctionFoldArea::mousePressEvent(QMouseEvent *event)
{
    QTextBlock block =codeEditor->getMousePositionBlock(event->y());
    int left = 0; //计算左边括号出现的次数
    int right =0;//计算边括号出现的次数
    //判断该块中是否有“{”、“}”，并确定“{”在“}”之前
    if(block.text().indexOf("{") != -1)
    {
        if(block.text().indexOf("{") != -1
                && block.text().indexOf("}") != -1
                && block.text().indexOf("{") > block.text().indexOf("}"))
        {
 //如果“}”在“{”之前则计数器减一
               right--;
        }
        while(block.isValid())
        {
             //如果有“{”出现，左括号的计数器会加一
            if(block.text().indexOf("{") !=-1)
            {
                left++;
            }
            if(block.text().indexOf("}")!= -1)
            {
        //如果有“}”出现则right计数器加一，left计数器减一，这样就能找到相匹配的括号

               right++;
               left--;
            }
            if(left==0)
            {
                //当left为0时，说明已找到匹配的括号
                break;
            }
            if(block.next().isVisible() == false)
                block.next().setVisible(true);
            else
                block.next().setVisible(false);
            codeEditor->funFold();
            codeEditor->hide();
            codeEditor->show();
            block = block.next();
        }
    }
}
void PlainTextEdit::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);

    QTextBlock block = firstVisibleBlock();
    while(block.isVisible() == false && block.blockNumber() != -1)
    {
        block = block.next();
    }
    if(block.blockNumber() == -1) return;
    int blockHeight = (int)blockBoundingRect(block).height();
    int visibleBlockNum = rect().height()/blockHeight+1;
    int blockCounter = 1;
    QPainter painter(viewport());
    //painter.setPen(Qt::black);
    painter.setPen(QColor(Qt::gray));
    int littleChange = firstVisibleBlock().blockNumber() == 0 ? 4 : 0;
    while(block.blockNumber() != -1 && blockCounter <= visibleBlockNum)
    {
        if(block.isVisible() == false)
        {
            if(block.previous().text().indexOf('{') == -1)
                painter.drawText(QRect(block.previous().text().length()*fontMetrics().width('a')+30,
                                       (int)blockBoundingGeometry(block.previous()).top()+littleChange,
                                       fontMetrics().width('a')*5,fontMetrics().height()),
                                 Qt::AlignCenter,QString("{...}"));
            else painter.drawText(QRect(block.previous().text().length()*fontMetrics().width('a')+100,
                                        (int)blockBoundingGeometry(block.previous()).top()+littleChange,
                                        fontMetrics().width('a')*5,fontMetrics().height()),
                                  Qt::AlignCenter,QString("...}"));
            painter.drawRoundRect(QRect(block.previous().text().length()*fontMetrics().width('a')+25,
                                   (int)blockBoundingGeometry(block.previous()).top()+littleChange,
                                   fontMetrics().width('a')*5+10,fontMetrics().height()));
            while(block.blockNumber() != -1 && block.isVisible() == false)
            {
                block = block.next();
            }
        }
        else block = block.next();
        if(block.blockNumber() != -1 && block.isVisible()) blockCounter++;
    }
}
