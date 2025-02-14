#pragma once


#include "bc_widget.h"


// ****************    标题     *****************
class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleBar(QWidget* parent = nullptr);

    void changeMaxIcon(bool isMax);

signals:
    void showMin();
    void showMax();
    void showClose();

protected:
    void initLayout();
    void connectSignals();
    void updateWidget();

private:
    QPushButton* minButton;
    QPushButton* maxButton;
    QPushButton* closeButton;
};





// ****************    背景     *****************
class BackgroundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BackgroundWidget(QWidget* parent = nullptr);

protected:
    void initLayout();
    void connectSignals();
    void updateWidget();

    void paintEvent(QPaintEvent* event) override;

private:
    QColor color[2];
};





// ****************    页面     *****************
class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

protected:
    void initLayout();
    void connectSignals();
    void updateWidget();

    void setWindowMaxMin();

    bool event(QEvent* e);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event);
    //void mouseDoubleClickEvent(QMouseEvent* event) override;


private:
    BcVLayout* m_layout;

    BackgroundWidget* m_page;
    CustomTitleBar*   m_title;

    bool b_maxed = 0;
    bool b_moved = 0;
    QPoint m_lastpos, m_dragStart, m_frameStart, dragPosition;
    QRect lastrect;



private:
    QPoint lastPos;  // 上次鼠标位置
    bool resizing;   // 是否正在缩放
    enum ResizeMode { None, TopLeft, Top, TopRight, Left, Right, BottomLeft, Bottom, BottomRight } resizeMode;  // 缩放模式
    const int resizeMargin = 10;  // 定义缩放区域的大小
};









