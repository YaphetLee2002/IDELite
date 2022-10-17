/*MoveWgt.h*/
/* 实现窗口的拖动 */
#ifndef MOVEWGT_H
#define MOVEWGT_H
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#define Move_Wgt                                                           \
private:                                                                   \
void mousePressEvent(QMouseEvent *event)                                   \
{                                                                          \
    m_isPressed = true;                                                    \
    m_startMovePos = event->globalPos()-this->frameGeometry().topLeft();   \
}                                                                          \
void mouseMoveEvent(QMouseEvent *event)                                    \
{                                                                          \
    if(m_isPressed)                                                        \
    {                                                                      \
        move(this->mapToGlobal(event->pos() - m_startMovePos));            \
    }                                                                      \
}                                                                          \
void mouseReleaseEvent(QMouseEvent *)                                      \
{                                                                          \
    m_isPressed = false;                                                   \
}                                                                          \
private:                                                                   \
    bool m_isPressed = false;                                              \
    QPoint m_startMovePos;

#endif // MOVEWGT_H
