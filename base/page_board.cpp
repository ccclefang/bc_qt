#include "page_board.h"


// ****************    标题     *****************
CustomTitleBar::CustomTitleBar(QWidget* parent) 
	: QWidget(parent)
{
	// 设置标题栏的外观
	setAutoFillBackground(true);
	setStyleSheet("background-color: #2c3e50;");

	// 创建按钮
	QPushButton* minButton = new QPushButton("Min", this);
	QPushButton* maxButton = new QPushButton("Max", this);
	QPushButton* closeButton = new QPushButton("Close", this);

	// 设置按钮的外观
	minButton->setStyleSheet("background-color: #34495e; color: white;");
	maxButton->setStyleSheet("background-color: #34495e; color: white;");
	closeButton->setStyleSheet("background-color: #e74c3c; color: white;");

	connect(minButton, &QPushButton::clicked, this, [&]() {
		this->showMin();
		});

	connect(maxButton, &QPushButton::clicked, this, [&]() {
		this->showMax();
		});

	connect(closeButton, &QPushButton::clicked, this, [&]() {
		this->showClose();
		});


	// 创建布局
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(minButton);
	layout->addWidget(maxButton);
	layout->addWidget(closeButton);
	layout->setAlignment(Qt::AlignRight);  // 按钮右对齐

	setLayout(layout);
}

void CustomTitleBar::initLayout()
{
}

void CustomTitleBar::connectSignals()
{
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
	radius = 10;
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
	painter.drawRoundedRect(rect(), radius, radius);

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
	BcHLayout* _layout = new BcHLayout(this, 30);
	m_page = new BackgroundWidget(this);
	_layout->addWidget(m_page, 1);

	// 阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setOffset(0, 0);
	effect->setColor(QColor(10, 10, 10));
	effect->setBlurRadius(30);
	m_page->setGraphicsEffect(effect);

	// 主布局
	m_layout = new BcVLayout(m_page);

	m_title = new CustomTitleBar(m_page);
	m_layout->addWidget(m_title);
	m_layout->addStretch(1);
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
		if (isMaximized()) 
			showNormal();
		else 
			showMaximized();
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
	if (event->button() == Qt::LeftButton) {
		m_dragStart = event->globalPos();
		m_frameStart = frameGeometry().topLeft();
		event->accept();
	}
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		QPoint delta = event->globalPos() - m_dragStart;
		move(m_frameStart + delta);
		event->accept();
	}
}

