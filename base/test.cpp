#include "test.h"

base::base(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    ColorPickerWidget* widget = new ColorPickerWidget();
    layout->addWidget(widget);

    BcButton* button = new BcButton("我的按钮", this);
    layout->addWidget(button);

    resize(400, 400);
}

base::~base()
{

}

