#include "bc_widget.h"



// *****************   布局    ******************
BcHLayout::BcHLayout(int margin, int space)
    :BcHLayout(nullptr, margin, space)
{}

BcHLayout::BcHLayout(QWidget* parent, int margin, int space)
    :QHBoxLayout(parent)
{
    setContentsMargins(margin, margin, margin, margin);
    setSpacing(space);
}


BcVLayout::BcVLayout(int margin, int space)
    :BcVLayout(nullptr, margin, space)
{}

BcVLayout::BcVLayout(QWidget* parent, int margin, int space)
    :QVBoxLayout(parent)
{
    setContentsMargins(margin, margin, margin, margin);
    setSpacing(space);
}




// ********************  按钮  ***********************

BcButton::BcButton(QString text, QWidget* parent)
    : QPushButton(text, parent), m_shadow(nullptr)
{
    setFocusPolicy(Qt::NoFocus);
    setFont(BcFont::font);

    // 设置格式
    if (m_style.isEmpty()) 
    {
        qDebug() << "===================" << BcSize::ComMargin;
        BcStyle::StyleValueMap["padding"] = QString("%1px ").arg(BcSize::ComMargin);
        m_style = BcStyle::ReadQssFile(":/base/qss/Button.qss");
    }

    qDebug() << m_style;

    setStyleSheet(m_style);
}





//void BcButton::setTypeStyle()
//{
//    // 初始化样式表
//    if (style.isEmpty()) {
//        StyleMap["padtopbottom"] = QString::number(Bc::ComMargin);
//        StyleMap["padleftright"] = QString::number(Bc::ComMarginLeftRight);
//        // 读取文件
//        style = Bc::ReadQssFile(":/qss/Resources/qss/Button.qss", StyleMap);
//    }
//
//    // 设置匹配样式表
//    switch (m_stylenum)
//    {
//    case 0:
//        setObjectName("BcButton");
//        break;
//    case 1:
//        setObjectName("ButtonYellow");
//        break;
//    case 2:
//        setObjectName("ButtonHead");
//        break;
//    case 3:
//        setObjectName("ButtonItem");
//        break;
//    case 4:
//        setObjectName("ReagentItem");
//        break;
//    }
//
//    // 样式
//    setStyleSheet(style);
//}
//
//void BcButton::setShadow(bool state)
//{
//    if (!m_shadow) {
//        m_shadow = new QGraphicsDropShadowEffect(this);
//        m_shadow->setOffset(0, 10);
//        m_shadow->setColor(QColor(178, 187, 228));
//        m_shadow->setBlurRadius(20);
//        setGraphicsEffect(m_shadow);
//    }
//    m_shadow->setEnabled(state);
//}
//
//void BcButton::resizeEvent(QResizeEvent* event)
//{
//    // 圆角
//    /*m_style = style + "QPushButton{border-radius:" + QString::number(height() / 2.0 - 1) + ";}";
//    setStyleSheet(m_style);*/
//
//}


//void BcButton::setTrText(QString text)
//{
//    qDebug() << LanguageState << text;
//    BcButton::setText(text);
//}



//
//void BcButton::changeEvent(QEvent* event)
//{
//    switch (event->type()) {
//    case QEvent::LanguageChange:
//        QPushButton::setText(QCoreApplication::translate("QObject", m_str_zh.toStdString().c_str()));
//        break;
//    default:
//        break;
//    }
//    QPushButton::changeEvent(event);
//}
