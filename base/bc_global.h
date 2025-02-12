#ifndef C_GLOBAL_H
#define C_GLOBAL_H

#include "bc_head.h"



// ******************  大小  *************************
// @
// @
// ***************************************************
static void initBcSize();

// 基础宽度
static QFontMetrics fm;
// 基础宽度
static QFontMetrics fmm;
// 基础宽度:屏幕宽度的100分之一
static int PxWidth;
// 基础高度：按钮高度
static int FmHeight;

// 圆角弧度：界面圆角
static int Radius;
// 边界宽度：界面边距
static int PageMargin;

// 控件边界
static int ComMargin;
// 控件边界：控件padding左右
static int ComMarginLeftRight;
// 控件宽度：按钮的宽度，标题中控件的最小宽度
static int ComWidth;








#endif

