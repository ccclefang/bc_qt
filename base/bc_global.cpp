#include "bc_global.h"

void BcStyle::Init()
{
    font = QFont("Microsoft YaHei", 11);

    titlefont = QFont("Microsoft YaHei", 21);

}


void BcSize::Init()
{
    fm = new QFontMetrics(BcStyle::font);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    PxWidth = screenRect.width() / 100.0;

    Radius = PxWidth;
    PageMargin = PxWidth * 2;
    ComMargin = PxWidth;

    cccout(Radius, PageMargin, ComMargin);
}

