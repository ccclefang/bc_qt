#pragma once

#include "bc_widget.h"


class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerWidget(QWidget* parent = nullptr);

private slots:
    void chooseColor();

private:
    QLineEdit* lineEdit;
};



class FontSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FontSelectorWidget(QWidget* parent = nullptr);

private slots:
    void selectFont();

private:
    QPushButton* fontButton;
    QLineEdit* fontLineEdit;
};



class LanguageSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LanguageSelectorWidget(QWidget* parent = nullptr);

private slots:
    void applyLanguage();

private:
    QComboBox* languageComboBox;
};
