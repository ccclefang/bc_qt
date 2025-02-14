#include "page_board.h"


int _radius = 10; /// 窗口圆角
int _margin = 30; // 阴影



// ****************    标题     *****************
CustomTitleBar::CustomTitleBar(QWidget* parent) 
	: QWidget(parent)
{
	// 布局
	initLayout();

	// 信号槽
	connectSignals();

	// 刷新
	updateWidget();

}

void CustomTitleBar::changeMaxIcon(bool isMax)
{
	if (isMax) {
		maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
	}
	else {
		maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
	}

}

void CustomTitleBar::initLayout()
{
	// 最小化按钮
	minButton = new QPushButton(this);
	minButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));

	// 最大化/还原按钮
	maxButton = new QPushButton(this);
	maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));

	// 关闭按钮
	closeButton = new QPushButton(this);
	closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));


	// 创建布局
	BcHLayout* layout = new BcHLayout(this, 5, 10);
	layout->addWidget(minButton);
	layout->addWidget(maxButton);
	layout->addWidget(closeButton);
	layout->setAlignment(Qt::AlignRight);  // 按钮右对齐

	setLayout(layout);
}

void CustomTitleBar::connectSignals()
{
	connect(minButton, &QPushButton::clicked, this, [&]() {
		this->showMin();
		});

	connect(maxButton, &QPushButton::clicked, this, [&]() {
		this->showMax();
		});

	connect(closeButton, &QPushButton::clicked, this, [&]() {
		this->showClose();
		});
}

void CustomTitleBar::updateWidget()
{

}






// ****************    背景     *****************
BackgroundWidget::BackgroundWidget(QWidget* parent)
	:QWidget(parent)
{
	// 布局
	initLayout();

	// 信号槽
	connectSignals();

	// 刷新
	updateWidget();
}

void BackgroundWidget::initLayout()
{

}

void BackgroundWidget::connectSignals()
{
	connect(BcSignalSlot::ptr(), &BcSignalSlot::updateSet, this, &BackgroundWidget::updateWidget);

}

void BackgroundWidget::updateWidget()
{
	color[0] = BcStyle::backcolor.lighter(50);
	color[1] = BcStyle::backcolor;
}

void BackgroundWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// 创建线性渐变
	QLinearGradient gradient(0, height(), width(), 0);
	gradient.setColorAt(0, color[0]);
	gradient.setColorAt(1, color[1]);

	// 设置渐变色作为背景
	painter.setBrush(gradient);
	painter.setPen(Qt::NoPen); 

	// 绘制背景
	painter.drawRoundedRect(rect(), _radius, _radius);

	QWidget::paintEvent(event);
}







// ****************    页面     *****************
BoardWidget::BoardWidget(QWidget* parent)
	:QWidget(parent)
{
	resize(600, 400);
	
	// 布局
	initLayout();
	
	// 信号槽
	connectSignals();

	// 刷新
	updateWidget();
}

void BoardWidget::initLayout()
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);

	// 背景控件
	BcHLayout* _layout = new BcHLayout(this);
	m_page = new BackgroundWidget(this);
	_layout->addWidget(m_page, 1);

	// 阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setOffset(0, 0);
	effect->setColor(QColor(10, 10, 10));
	effect->setBlurRadius(_margin);
	m_page->setGraphicsEffect(effect);

	// 主布局
	m_layout = new BcVLayout(m_page);

	m_title = new CustomTitleBar(m_page);
	m_layout->addWidget(m_title);
	m_layout->addStretch(1);


	setAttribute(Qt::WA_Hover, true);
	setMouseTracking(true);  // 启用鼠标跟踪
}


void BoardWidget::connectSignals()
{
	// 设置更新
	connect(BcSignalSlot::ptr(), &BcSignalSlot::updateSet, this, &BoardWidget::updateWidget);

	// 最小化
	connect(m_title, &CustomTitleBar::showMin, this, [&]() {
		showMinimized();
		});
	connect(m_title, &CustomTitleBar::showMax, this, [&]() {
		setWindowMaxMin();
		});
	connect(m_title, &CustomTitleBar::showClose, this, [&]() {
		close();
		});

}

void BoardWidget::updateWidget()
{
	
}




void BoardWidget::setWindowMaxMin()
{
	if (b_maxed)
	{
		b_maxed = 0;

		// 取消最大化
		setContentsMargins(_margin, _margin, _margin, _margin);
		m_title->changeMaxIcon(1);
		setGeometry(lastrect);
		//showNormal();

	}
	else
	{
		b_maxed = 1;

		// 最大化
		setContentsMargins(0, 0, 0, 0);
		m_title->changeMaxIcon(0);

		m_lastpos = pos();
		lastrect = geometry();

		move(0, 0);
		//showMaximized();

		resize(700, 500);
	}
	
}

//
//void BoardWidget::mousePressEvent(QMouseEvent* event)
//{
//	if (event->button() == Qt::LeftButton) 
//	{
//		b_moved = 1;
//		dragPosition = event->globalPos() - frameGeometry().topLeft();
//		event->accept();
//	}
//}
//
//
//void BoardWidget::mouseMoveEvent(QMouseEvent* event)
//{
//	if (b_moved && event->buttons() == Qt::LeftButton && underMouse())
//	{
//		move(event->globalPos() - dragPosition);
//		event->accept();
//	}
//}
//
//void BoardWidget::mouseDoubleClickEvent(QMouseEvent* event)
//{
//	// 处理双击事件
//	if (event->button() == Qt::LeftButton) 
//	{
//		b_moved = 0;
//		dragPosition = event->globalPos();
//		event->accept(); 
//
//		setWindowMaxMin();
//	}
//}
//


bool BoardWidget::event(QEvent* e)
{
	if (QEvent::HoverMove == e->type())//鼠标移动
	{
		QHoverEvent* event = static_cast<QHoverEvent*>(e);
		if (!resizing) 
		{
			// 如果不在缩放区域，显示相应的光标
			if (event->pos().x() < resizeMargin) {
				if (event->pos().y() < resizeMargin) {
					setCursor(Qt::SizeFDiagCursor);  // 左上角对角线
				}
				else if (event->pos().y() > height() - resizeMargin) {
					setCursor(Qt::SizeBDiagCursor);  // 左下角对角线
				}
				else {
					setCursor(Qt::SizeHorCursor);  // 左侧水平
				}
			}
			else if (event->pos().x() > width() - resizeMargin) {
				if (event->pos().y() < resizeMargin) {
					setCursor(Qt::SizeBDiagCursor);  // 右上角对角线
				}
				else if (event->pos().y() > height() - resizeMargin) {
					setCursor(Qt::SizeFDiagCursor);  // 右下角对角线
				}
				else {
					setCursor(Qt::SizeHorCursor);  // 右侧水平
				}
			}
			else if (event->pos().y() < resizeMargin) {
				setCursor(Qt::SizeVerCursor);  // 上部垂直
			}
			else if (event->pos().y() > height() - resizeMargin) {
				setCursor(Qt::SizeVerCursor);  // 下部垂直
			}
			else {
				setCursor(Qt::ArrowCursor);  // 默认光标
			}
		}
	}

	return QWidget::event(e);
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) 
	{
		lastPos = event->globalPos();
		resizing = false;

		// 检测是否在窗口边缘区域进行缩放
		if (event->pos().x() < resizeMargin) 
		{
			if (event->pos().y() < resizeMargin) {
				resizeMode = TopLeft;
				setCursor(Qt::SizeFDiagCursor);  // 左上角对角线
			}
			else if (event->pos().y() > height() - resizeMargin) {
				resizeMode = BottomLeft;
				setCursor(Qt::SizeBDiagCursor);  // 左下角对角线
			}
			else {
				resizeMode = Left;
				setCursor(Qt::SizeHorCursor);  // 左侧水平
			}
		}
		else if (event->pos().x() > width() - resizeMargin) {
			if (event->pos().y() < resizeMargin) {
				resizeMode = TopRight;
				setCursor(Qt::SizeBDiagCursor);  // 右上角对角线
			}
			else if (event->pos().y() > height() - resizeMargin) {
				resizeMode = BottomRight;
				setCursor(Qt::SizeFDiagCursor);  // 右下角对角线
			}
			else {
				resizeMode = Right;
				setCursor(Qt::SizeHorCursor);  // 右侧水平
			}
		}
		else if (event->pos().y() < resizeMargin) {
			setCursor(Qt::SizeVerCursor);  // 上部垂直
			resizeMode = Top;
		}
		else if (event->pos().y() > height() - resizeMargin) {
			setCursor(Qt::SizeVerCursor);  // 下部垂直
			resizeMode = Bottom;
		}
		else {
			resizing = false;
			return;
		}

		resizing = true;  // 开始缩放
	}
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (resizing) {
		QPoint delta = event->globalPos() - lastPos;
		lastPos = event->globalPos();

		switch (resizeMode) 
		{
		case TopLeft:
			resize(width() - delta.x(), height() - delta.y());
			move(x() + delta.x(), y() + delta.y());
			break;
		case Top:
			resize(width(), height() - delta.y());
			move(x(), y() + delta.y());
			break;
		case TopRight:
			resize(width() + delta.x(), height() - delta.y());
			move(x(), y() + delta.y());
			break;
		case Left:
			resize(width() - delta.x(), height());
			move(x() + delta.x(), y());
			break;
		case Right:
			resize(width() + delta.x(), height());
			break;
		case BottomLeft:
			resize(width() - delta.x(), height() + delta.y());
			move(x() + delta.x(), y());
			break;
		case Bottom:
			resize(width(), height() + delta.y());
			break;
		case BottomRight:
			resize(width() + delta.x(), height() + delta.y());
			break;
		}
	}
}

void BoardWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		resizing = false;
		setCursor(Qt::ArrowCursor);  // 恢复默认光标
	}
}
