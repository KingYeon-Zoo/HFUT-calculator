#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QFrame>
#include <QFont>
#include "calculatorengine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 数字按钮槽函数
    void onNumberClicked();
    
    // 运算符按钮槽函数
    void onOperatorClicked();
    void onBinaryOperatorClicked();
    void onNotClicked();  // NOT 一元运算符特殊处理
    
    // 功能按钮槽函数
    void onEqualsClicked();
    void onClearClicked();
    void onClearEntryClicked();
    void onModeToggleClicked();
    
    // 计算引擎信号响应
    void onDisplayChanged(const QString& value);
    void onErrorOccurred(const QString& error);
    void onModeChanged(CalculatorMode mode);

private:
    Ui::MainWindow *ui;
    CalculatorEngine *engine;
    
    // UI 组件
    QLineEdit *display;
    QLabel *modeLabel;
    QLabel *baseLabel;
    
    // 按钮组
    QButtonGroup *numberButtons;
    QButtonGroup *operatorButtons;
    QButtonGroup *binaryOperatorButtons;
    QButtonGroup *functionButtons;
    
    // 数字按钮 (0-9, A-F)
    QPushButton *btn0, *btn1, *btn2, *btn3, *btn4;
    QPushButton *btn5, *btn6, *btn7, *btn8, *btn9;
    QPushButton *btnA, *btnB, *btnC, *btnD, *btnE, *btnF;
    
    // 普通运算符按钮
    QPushButton *btnAdd, *btnSubtract, *btnMultiply, *btnDivide;
    
    // 二进制运算符按钮
    QPushButton *btnAnd, *btnOr, *btnXor, *btnNot;
    QPushButton *btnLeftShift, *btnRightShift;
    
    // 功能按钮
    QPushButton *btnEquals, *btnClear, *btnClearEntry;
    QPushButton *btnModeToggle;
    QPushButton *btnDecimal, *btnHex, *btnBinary;
    
    // 布局
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *displayLayout;
    QHBoxLayout *modeLayout;
    QGridLayout *buttonLayout;
    
    // 私有方法
    void setupUI();
    void setupButtons();
    void setupLayouts();
    void setupConnections();
    void setupStyles();
    
    void updateButtonStates();
    void updateModeDisplay();
    void updateBaseDisplay();
    
    // Apple 风格样式
    void applyAppleStyle();
    QString getButtonStyle(const QString& type) const;
    QString getDisplayStyle() const;
    QString getWindowStyle() const;
    
    // 按钮管理
    void setButtonsEnabled(const QList<QPushButton*>& buttons, bool enabled);
    void setButtonsVisible(const QList<QPushButton*>& buttons, bool visible);
    
    // 工具方法
    QPushButton* createButton(const QString& text, const QString& objectName = "");
    void connectNumberButton(QPushButton* button, const QString& value);
    void connectOperatorButton(QPushButton* button, const QString& op);
    void connectBinaryOperatorButton(QPushButton* button, const QString& op);
};

#endif // MAINWINDOW_H 