#ifndef BC_GLOBAL_H
#define BC_GLOBAL_H

#include "bc_head.h"



// ******************  样式  *************************
// @
// @
// ***************************************************
class BcStyle : SingletonInit<BcStyle>
{
	SINGLETON_INIT_IDX(BcStyle, 1)
public:
	void Init();

public:
	// 基础字体
	inline static QFont font;

	// 小号字体
	inline static QFont titlefont;

public:
	QMap<QString, QColor> ColorMap;
};







// ******************  大小  *************************
// @
// @
// ***************************************************
class BcSize : SingletonInit<BcSize>
{
	SINGLETON_INIT_IDX(BcSize, 2)

public:
	void Init();

public:
	// 基础度量
	inline static QFontMetrics* fm;
	
	// 基础宽度:屏幕宽度的100分之一
	inline static int PxWidth;

	// 基础高度
	inline static int FmHeight;
	// 圆角弧度：界面圆角
	inline static int Radius;
	// 边界宽度：界面边距
	inline static int PageMargin;
	// 边界宽度：控件边界
	inline static int ComMargin;

};








#endif

