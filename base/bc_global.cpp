#include "bc_global.h"


void BcJson::Init()
{
	filepath = "config.json";

	// 读取config
	QFile file(filepath);
	if (!file.exists())
	{
		qWarning() << "File does not exist!";
		return;
	}
	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning() << "Failed to open file:" << file.errorString();
		return;
	}
	QByteArray data = file.readAll();
	file.close();
	QJsonDocument doc = QJsonDocument::fromJson(data);
	if (doc.isNull())
	{
		qWarning() << "Failed to create JSON document!";
		return;
	}


	// 获取 JSON 根对象
	jsonObj = doc.object();  
}

QJsonObject BcJson::getColor()
{
	auto color = jsonObj["color"].toObject();
	return color;
}

void BcJson::modifyColor(QString str)
{
	// 主题颜色
	auto themeColor = QColor(str);
	// 背景色：稍微降低亮度
	auto backgroundColor = themeColor.darker(120);
	// 按钮色：稍微加深主色
	auto buttonColor = themeColor.darker(110);
	// 文字色：对比度高，使用黑色或白色
	if (themeColor.lightness() < 128) {
		auto textColor = QColor(255, 255, 255);  // 白色文字
	}
	else {
		auto textColor = QColor(0, 0, 0);  // 黑色文字
	}
	// hover 按钮色：用更亮的版本
	auto buttonHoverColor = themeColor.lighter(120);


}


bool BcJson::saveJson() const {
	QFile file(filepath);
	if (!file.open(QIODevice::WriteOnly)) {
		qWarning() << "Couldn't open file for writing:" << filepath;
		return false;
	}

	// 将 QJsonObject 转换为 QJsonDocument
	QJsonDocument doc(jsonObj);
	file.write(doc.toJson());
	file.close();

	return true;
}



// ******************  字体  *************************
// @
// @
// ***************************************************
void BcFont::Init()
{
	// 设置字体
	font = QFont("Microsoft YaHei", 11);
	titlefont = QFont("Microsoft YaHei", 21);
}




// ******************  大小  *************************
// @
// @
// ***************************************************
void BcSize::Init()
{
	fm = new QFontMetrics(BcFont::font);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	PxWidth = screenRect.width() / 100.0;

	Radius = PxWidth;
	PageMargin = PxWidth * 2;
	ComMargin = PxWidth;

	// cccout(Radius, PageMargin, ComMargin);
}







// ******************  样式  *************************
// @
// @
// ***************************************************
void BcStyle::Init()
{
	// 设置颜色
	QJsonObject colorsObj = BcJson::ptr()->getColor();
	for (auto it = colorsObj.begin(); it != colorsObj.end(); ++it)
	{
		ColorMap[it.key()] = it.value().toString();
	}

	maincolor = ColorMap["maincolor"];
	confirmcolor = ColorMap["confirmcolor"];
	lightcolor = ColorMap["lightcolor"];
	backcolor = ColorMap["backcolor"];
	fontcolor = ColorMap["fontcolor"];
	disablecolor = ColorMap["disablecolor"];

	// 设置位置变量
	StyleValueMap["padding"] = BcSize::ComMargin;
}



QString BcStyle::ReadQssFile(const QString filePath)
{
	static QMap<QString, QString> cache;

	if (cache.find(filePath) == cache.end())
	{
		QString strStyleSheet = "";
		QFile file(filePath);
		file.open(QFile::ReadOnly);
		if (file.isOpen()) {
			strStyleSheet = file.readAll();
		}
		else {
			qDebug() << filePath;
			qDebug("Bc::ReadQssFile filed");
		}
		cache[filePath] = strStyleSheet;
	}

	return cache[filePath];



	// 原始样式表
	QString strStyleSheet = cache[filePath];

	// 替换颜色
	QMapIterator<QString, QColor> citer(ColorMap);
	while (citer.hasNext()) {
		citer.next();
		QString style = "@" + citer.key();
		strStyleSheet.replace(style, citer.value().name());
	}

	// 替换大小
	QMapIterator<QString, QString> iter(StyleValueMap);
	while (iter.hasNext()) {
		iter.next();
		QString key = iter.key();
		if (key[0] != '@')
			key = "@" + key;
		if (strStyleSheet.contains(key))
			strStyleSheet.replace(key, iter.value());
	}

	return strStyleSheet;
}




QString BcStyle::RegistQssStyle(const QString qssname, QWidget* widget)
{
	BcStyle::ReadQssFile(":/base/qss/" + qssname);

	return QString();
}

QString BcStyle::UpdateQssStyle()
{
	for (auto widget : objvec)
	{
		if (widget->isVisible())
		{

		}
	}

	return QString();
}

