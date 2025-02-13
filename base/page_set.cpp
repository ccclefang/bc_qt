#include "page_set.h"


ColorPickerWidget::ColorPickerWidget(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    // 创建按钮
    QPushButton* colorButton = new QPushButton("Select Color", this);
    layout->addWidget(colorButton);

    // 创建 LineEdit 来显示颜色
    lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);

    // 连接按钮的点击信号到槽函数
    connect(colorButton, &QPushButton::clicked, this, &ColorPickerWidget::chooseColor);
}

void ColorPickerWidget::chooseColor()
{
    // 打开颜色选择对话框
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose Color");

    if (color.isValid()) {
        // 获取选中颜色的十六进制表示
        QString colorHex = color.name();  // QColor::name() 返回格式 "#RRGGBB"
        // 将颜色设置到 LineEdit
        lineEdit->setText(colorHex);

        auto map = BcStyle::ColorMap;

        // 设置到样式文件
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        QMapIterator<QString, QColor> it(map);
        while (it.hasNext()) {
            it.next();
            jsonObject[it.key()] = it.value().name();
        }
        QJsonDocument doc(jsonObject);
        QFile file("config.json");
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning() << "Couldn't open file for writing.";
            return;
        }

        // 写入文件
        file.write(doc.toJson());
        file.close();
    }
}





FontSelectorWidget::FontSelectorWidget(QWidget* parent) : QWidget(parent) {
    // 创建 UI 控件
    fontButton = new QPushButton("选择字体", this);
    fontLineEdit = new QLineEdit(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(fontButton);
    layout->addWidget(fontLineEdit);

    connect(fontButton, &QPushButton::clicked, this, &FontSelectorWidget::selectFont);
}

void FontSelectorWidget::selectFont() {
    // 打开字体选择对话框
    bool ok;
    QFont font = QFontDialog::getFont(&ok, fontLineEdit->font(), this);

    if (ok) {
        // 如果用户选择了字体，更新显示
        fontLineEdit->setFont(font);
        fontLineEdit->setText(font.family());
    }
}




LanguageSelectorWidget::LanguageSelectorWidget(QWidget* parent) : QWidget(parent) {
    // 创建控件
    languageComboBox = new QComboBox(this);
    languageComboBox->addItem("English", "en");
    languageComboBox->addItem("中文", "zh");

    QPushButton* applyButton = new QPushButton("应用", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(languageComboBox);
    layout->addWidget(applyButton);

    connect(applyButton, &QPushButton::clicked, this, &LanguageSelectorWidget::applyLanguage);
}

void LanguageSelectorWidget::applyLanguage() {
    QString languageCode = languageComboBox->currentData().toString();
    QTranslator* translator = new QTranslator(this);

    if (languageCode == "zh") {
        translator->load(":/translations/myapp_zh.qm");
    }
    else {
        translator->load(":/translations/myapp_en.qm");
    }

    qApp->installTranslator(translator);

    // 重载界面或更新文本
    // 更新界面上的文本
}
