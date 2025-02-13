#ifndef BC_WIDGET_H
#define BC_WIDGET_H


#include "bc_global.h"

// *****************   布局    ******************
class BcHLayout : public QHBoxLayout
{
	Q_OBJECT
public:
	BcHLayout(int margin = 0, int space = 0);
	BcHLayout(QWidget* parent, int margin = 0, int space = 0);

};

class BcVLayout : public QVBoxLayout
{
	Q_OBJECT
public:
	BcVLayout(int margin = 0, int space = 0);
	BcVLayout(QWidget* parent, int margin = 0, int space = 0);

};



// *****************   按钮    ******************
class BcButton : public QPushButton
{
	Q_OBJECT
public:
	BcButton(QString text = "", QWidget* parent = nullptr);


	//void setTypeStyle();
	//void setShadow(bool state = 1);

	//void resizeEvent(QResizeEvent* event);

	//void changeEvent(QEvent* e);

private:
	QString m_str_zh;

	QString m_style;

	QGraphicsDropShadowEffect* m_shadow;
};






#endif