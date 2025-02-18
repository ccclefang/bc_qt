#ifndef BC_SCALED_H
#define BC_SCALED_H

#include "bc_widget.h"

class BcScaledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BcScaledWidget(QWidget* parent = nullptr, int resizeMargin = 0, int resizeWidth = 5);

protected:
    bool setMouse(QPoint mousepos);
    void setWindowMaxMin();
    void setMoveScaled(int x, int y, int w, int h);

    bool event(QEvent* e);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    bool b_maxed = 0;

    // 拖拽和缩放起点
    QRect beginrect;
    QPoint beginPos;
    // 缩放状态
    bool resizing = 0;
    // 缩放区域
    const int resizeWidth; // 缩放区域的宽度
    const int resizeMargin; // 缩放区域到窗口边界的距离
    // 缩放模式
    enum ResizeMode { None, TopLeft, Top, TopRight, Left, Right, BottomLeft, Bottom, BottomRight } resizeMode; 
};




#endif // BC_SCALED_H
