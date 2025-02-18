#pragma once


#include "bc_widget.h"
#include "bc_scaledwidget.h"




// ****************    标题     *****************
class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTitleBar(QWidget* parent = nullptr);

    void setMax();
    void setNoraml();

signals:
    void showMin();
    void showMax();
    void showNoraml();
    void showClose();

protected:
    void initLayout();
    void connectSignals();
    void updateWidget();

private:
    QPushButton* minButton;
    QPushButton* maxButton;
    QPushButton* normalButton;
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
class BoardWidget : public BcScaledWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);

protected:
    void initLayout();
    void connectSignals();
    void updateWidget();

    void mousePressEvent(QMouseEvent* event);

    // bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private:
    void setWindowMax();
    void setWindowNormal();


private:
    BcVLayout* m_layout;

    BackgroundWidget* m_page;
    CustomTitleBar*   m_title;
};


