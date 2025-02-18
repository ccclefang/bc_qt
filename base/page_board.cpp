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


void CustomTitleBar::initLayout()
{
	// 最小化按钮
	minButton = new QPushButton(this);
	minButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));

	// 最大化
	maxButton = new QPushButton(this);
	maxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));

	// 还原按钮
	normalButton = new QPushButton(this);
	normalButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));

	// 关闭按钮
	closeButton = new QPushButton(this);
	closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));

	// 创建布局
	BcHLayout* layout = new BcHLayout(this, 5, 10);
	layout->addWidget(minButton);
	layout->addWidget(maxButton);
	layout->addWidget(normalButton);
	layout->addWidget(closeButton);
	layout->setAlignment(Qt::AlignRight);  // 按钮右对齐

	setLayout(layout);
}

void CustomTitleBar::setMax()
{
	maxButton->hide();
	normalButton->show();
}

void CustomTitleBar::setNoraml()
{
	maxButton->show();
	normalButton->hide();
}

void CustomTitleBar::connectSignals()
{
	connect(minButton, &QPushButton::clicked, this, [&]() {
		emit showMin();
		});

	connect(maxButton, &QPushButton::clicked, this, [&]() {
		emit showMax();
		});

	connect(normalButton, &QPushButton::clicked, this, [&]() {
		emit showNoraml();
		});

	connect(closeButton, &QPushButton::clicked, this, [&]() {
		emit showClose();
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
	:BcScaledWidget(parent, _margin)
{
	// 布局
	initLayout();
	
	// 信号槽
	connectSignals();

	// 刷新
	updateWidget();

	// 显示窗口
	setWindowNormal();
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

	// 标题
	m_title = new CustomTitleBar(m_page);
	m_layout->addWidget(m_title);
	m_layout->addStretch(1);

	setAttribute(Qt::WA_Hover, true);
	setMouseTracking(true);  // 启用鼠标跟踪

	this->winId();//必须，不然nativeEvent不触发
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
		setWindowMax();
		});
	connect(m_title, &CustomTitleBar::showNoraml, this, [&]() {
		setWindowNormal();
		});
	connect(m_title, &CustomTitleBar::showClose, this, [&]() {
		close();
		});
}

void BoardWidget::updateWidget()
{

}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && isMaximized())
	{
		float posx = event->globalPos().x();
		float posy = event->globalPos().y();
		float ratio = posx * 1.0 / geometry().width();

		setWindowNormal();

		move(posx - geometry().width() * ratio, posy - _margin - 10);
		event->accept();
	}

	BcScaledWidget::mousePressEvent(event);
}



//
//bool BoardWidget::nativeEvent(const QByteArray& eventType, void* message, long* result)
//{
//	MSG* msg = (MSG*)message;
//	switch (msg->message) {
//		//没有这一段，将不会显示窗口
//		case WM_NCCALCSIZE:
//			return true;
//
//		case WM_NCHITTEST:
//		{
//			//qDebug() << "触发WM_NCHITTEST";
//			qreal ratio = 1.0;
//			long x = GET_X_LPARAM(msg->lParam) / ratio;
//			long y = GET_Y_LPARAM(msg->lParam) / ratio;
//			QPoint pos = mapFromGlobal(QPoint(x, y));
//			//qDebug() << "pos = " << pos;
//			if (pos.y() > 10 && ui->widget_title2->rect().contains(pos)) {
//				//qDebug() << "标题栏被按下";
//				// 根据当前鼠标的位置显示不同的样式;
//				*result = HTCAPTION;
//				return true;
//			}
//		}
//		case WM_GETMINMAXINFO:
//		{
//			if (::IsZoomed(msg->hwnd)) {
//				isMaxShow = true;
//				showFlag = true;
//				// 最大化时会超出屏幕，所以填充边框间距
//				RECT frame = { 0, 0, 0, 0 };
//				AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
//				frame.left = abs(frame.left);
//				frame.top = abs(frame.bottom);
//				this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
//			}
//			else {
//				isMaxShow = false;
//				showFlag = false;
//			}
//			*result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
//			return true;
//		}
//	}
//	return QMainWindow::nativeEvent(eventType, message, result);
//}




void BoardWidget::setWindowMax()
{
	layout()->setContentsMargins(0, 0, 0, 0);
	showMaximized();
	m_title->setMax();
}

void BoardWidget::setWindowNormal()
{
	layout()->setContentsMargins(_margin, _margin, _margin, _margin);
	showNormal();
	m_title->setNoraml();
}
