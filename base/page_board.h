#pragma once


#include "bc_widget.h"


// ****************    标题     *****************
class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleBar(QWidget* parent = nullptr);

signals:
    void showMin();
    void showMax();
    void showClose();

protected:
    void initLayout();
    void connectSignals();
    void updateWidget();
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
    int radius = 10;

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

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;


private:
    BcVLayout* m_layout;

    BackgroundWidget* m_page;
    CustomTitleBar*   m_title;


    QPoint m_dragStart, m_frameStart;
};

