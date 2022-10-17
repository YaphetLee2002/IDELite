/*DragWgt.h*/
/* 实现窗口的拖动伸缩 */
#ifndef DRAGWGT_H
#define DRAGWGT_H
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include "Windows.h"
#define Drag_Wgt                                                                          \
bool nativeEvent(const QByteArray &eventType, void *message, long *result)                \
{                                                                                         \
    MSG* pMsg = (MSG*)message;                                                            \
    switch (pMsg->message)                                                                \
    {                                                                                     \
    case WM_NCHITTEST:                                                                    \
    {                                                                                     \
        QPoint pos = mapFromGlobal(QPoint(LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)));   \
        bool bHorLeft = pos.x() < g_nBorder;                                              \
        bool bHorRight = pos.x() > width() - g_nBorder;                                   \
        bool bVertTop = pos.y() < g_nBorder;                                              \
        bool bVertBottom = pos.y() > height() - g_nBorder;                                \
        if (bHorLeft && bVertTop)                                                         \
        {                                                                                 \
            *result = HTTOPLEFT;                                                          \
        }                                                                                 \
        else if (bHorLeft && bVertBottom)                                                 \
        {                                                                                 \
            *result = HTBOTTOMLEFT;                                                       \
        }                                                                                 \
        else if (bHorRight && bVertTop)                                                   \
        {                                                                                 \
            *result = HTTOPRIGHT;                                                         \
        }                                                                                 \
        else if (bHorRight && bVertBottom)                                                \
        {                                                                                 \
            *result = HTBOTTOMRIGHT;                                                      \
        }                                                                                 \
        else if (bHorLeft)                                                                \
        {                                                                                 \
            *result = HTLEFT;                                                             \
        }                                                                                 \
        else if (bHorRight)                                                               \
        {                                                                                 \
            *result = HTRIGHT;                                                            \
        }                                                                                 \
        else if (bVertTop)                                                                \
        {                                                                                 \
            *result = HTTOP;                                                              \
        }                                                                                 \
        else if (bVertBottom)                                                             \
        {                                                                                 \
            *result = HTBOTTOM;                                                           \
        }                                                                                 \
        else                                                                              \
        {                                                                                 \
            return false;                                                                 \
        }                                                                                 \
        return true;                                                                      \
    }                                                                                     \
        break;                                                                            \
    default:                                                                              \
        break;                                                                            \
    }                                                                                     \
    return QWidget::nativeEvent(eventType, message, result);                              \
}                                                                                         \
private:                                                                                  \
    int g_nBorder = 4;

#endif // DRAGWGT_H

