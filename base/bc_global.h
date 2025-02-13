#ifndef BC_GLOBAL_H
#define BC_GLOBAL_H

#include "bc_head.h"



// ******************  配置  *************************
// @
// @
// ***************************************************
class BcJson : public SingletonInit<BcJson>
{
	SINGLETON_INIT_IDX(BcJson, 0)

public:
	void Init();

public:
	// 颜色
	QJsonObject getColor();
	void modifyColor(QString color);


	// 保存修改后的 JSON 数据到文件
	bool saveJson() const;

private:
	QString filepath;

	QJsonObject jsonObj;

};





// ******************  字体  *************************
// @
// @
// ***************************************************
class BcFont : public SingletonInit<BcFont>
{
	SINGLETON_INIT_IDX(BcFont, 1)
public:
	void Init();

public:
	// 基础字体
	inline static QFont font;

	// 小号字体
	inline static QFont titlefont;

};



// ******************  大小  *************************
// @
// @
// ***************************************************
class BcSize : public SingletonInit<BcSize>
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





// ******************  样式  *************************
// @
// @
// ***************************************************
class BcStyle : public SingletonInit<BcStyle>
{
	SINGLETON_INIT_IDX(BcStyle, 3)
public:
	void Init();

public:
	// 获取QSS
	static QString ReadQssFile(const QString filePath);

	// 注册控件
	static QString RegistQssStyle(const QString qssname, QWidget* widget);

	// 样式刷新
	static QString UpdateQssStyle();


public:
	// 颜色表
	inline static QMap<QString, QColor> ColorMap;
	inline static QColor maincolor;
	inline static QColor confirmcolor;
	inline static QColor lightcolor;
	inline static QColor backcolor;
	inline static QColor fontcolor;
	inline static QColor disablecolor;



	// 替换表
	inline static QMap<QString, QString> StyleValueMap;

	// 样式表
	inline static QMap<QString, QString> StyleSheetMap;

	
private:
	inline static QVector<QWidget*> objvec;
};





// ******************  信号槽  ************************
// @
// @
// ***************************************************
class BcSignalSlot :public QObject
{
	Q_OBJECT

	SINGLETON(BcSignalSlot)

public:


signals:
	// 通用设置
	void updateSet();
	void updateSetColor();
	void updateSetFont();
	void updateSetSize();

};



#endif