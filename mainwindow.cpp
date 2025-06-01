#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QFont>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , engine(new CalculatorEngine(this))
{
    ui->setupUi(this);
    setupUI();
    setupButtons();
    setupLayouts();
    setupConnections();
    setupStyles();
    
    // 初始化显示
    updateModeDisplay();
    updateBaseDisplay();
    updateButtonStates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // 设置窗口属性
    setWindowTitle("HFUT Calculator");
    setFixedSize(400, 600);
    
    // 获取 UI 组件引用
    display = ui->displayLineEdit;
    modeLabel = ui->modeLabel;
    baseLabel = ui->baseLabel;
    
    // 设置显示器初始状态
    display->setText("0");
    display->setReadOnly(true);
}

void MainWindow::setupButtons()
{
    // 创建按钮组
    numberButtons = new QButtonGroup(this);
    operatorButtons = new QButtonGroup(this);
    binaryOperatorButtons = new QButtonGroup(this);
    functionButtons = new QButtonGroup(this);
    
    // 获取现有按钮引用
    btnModeToggle = ui->btnModeToggle;
    btnClear = ui->btnClear;
    btnClearEntry = ui->btnClearEntry;
    btnDivide = ui->btnDivide;
    
    // 创建数字按钮 (0-9)
    btn0 = createButton("0", "btn0");
    btn1 = createButton("1", "btn1");
    btn2 = createButton("2", "btn2");
    btn3 = createButton("3", "btn3");
    btn4 = createButton("4", "btn4");
    btn5 = createButton("5", "btn5");
    btn6 = createButton("6", "btn6");
    btn7 = createButton("7", "btn7");
    btn8 = createButton("8", "btn8");
    btn9 = createButton("9", "btn9");
    
    // 创建十六进制字母按钮 (A-F)
    btnA = createButton("A", "btnA");
    btnB = createButton("B", "btnB");
    btnC = createButton("C", "btnC");
    btnD = createButton("D", "btnD");
    btnE = createButton("E", "btnE");
    btnF = createButton("F", "btnF");
    
    // 创建普通运算符按钮
    btnAdd = createButton("+", "btnAdd");
    btnSubtract = createButton("−", "btnSubtract");
    btnMultiply = createButton("×", "btnMultiply");
    
    // 创建二进制运算符按钮
    btnAnd = createButton("AND", "btnAnd");
    btnOr = createButton("OR", "btnOr");
    btnXor = createButton("XOR", "btnXor");
    btnNot = createButton("NOT", "btnNot");
    btnLeftShift = createButton("<<", "btnLeftShift");
    btnRightShift = createButton(">>", "btnRightShift");
    
    // 创建功能按钮
    btnEquals = createButton("=", "btnEquals");
    btnDecimal = createButton("DEC", "btnDecimal");
    btnHex = createButton("HEX", "btnHex");
    btnBinary = createButton("BIN", "btnBinary");
    
    // 将按钮添加到按钮组
    numberButtons->addButton(btn0, 0);
    numberButtons->addButton(btn1, 1);
    numberButtons->addButton(btn2, 2);
    numberButtons->addButton(btn3, 3);
    numberButtons->addButton(btn4, 4);
    numberButtons->addButton(btn5, 5);
    numberButtons->addButton(btn6, 6);
    numberButtons->addButton(btn7, 7);
    numberButtons->addButton(btn8, 8);
    numberButtons->addButton(btn9, 9);
    numberButtons->addButton(btnA, 10);
    numberButtons->addButton(btnB, 11);
    numberButtons->addButton(btnC, 12);
    numberButtons->addButton(btnD, 13);
    numberButtons->addButton(btnE, 14);
    numberButtons->addButton(btnF, 15);
    
    operatorButtons->addButton(btnAdd);
    operatorButtons->addButton(btnSubtract);
    operatorButtons->addButton(btnMultiply);
    operatorButtons->addButton(btnDivide);
    
    binaryOperatorButtons->addButton(btnAnd);
    binaryOperatorButtons->addButton(btnOr);
    binaryOperatorButtons->addButton(btnXor);
    binaryOperatorButtons->addButton(btnNot);
    binaryOperatorButtons->addButton(btnLeftShift);
    binaryOperatorButtons->addButton(btnRightShift);
    
    functionButtons->addButton(btnEquals);
    functionButtons->addButton(btnClear);
    functionButtons->addButton(btnClearEntry);
    functionButtons->addButton(btnModeToggle);
    functionButtons->addButton(btnDecimal);
    functionButtons->addButton(btnHex);
    functionButtons->addButton(btnBinary);
}

void MainWindow::setupLayouts()
{
    // 获取按钮布局
    QGridLayout *buttonLayout = qobject_cast<QGridLayout*>(ui->buttonFrame->layout());
    
    if (buttonLayout) {
        // 第一行已在 UI 文件中定义
        
        // 第二行：7 8 9 ×
        buttonLayout->addWidget(btn7, 1, 0);
        buttonLayout->addWidget(btn8, 1, 1);
        buttonLayout->addWidget(btn9, 1, 2);
        buttonLayout->addWidget(btnMultiply, 1, 3);
        
        // 第三行：4 5 6 −
        buttonLayout->addWidget(btn4, 2, 0);
        buttonLayout->addWidget(btn5, 2, 1);
        buttonLayout->addWidget(btn6, 2, 2);
        buttonLayout->addWidget(btnSubtract, 2, 3);
        
        // 第四行：1 2 3 +
        buttonLayout->addWidget(btn1, 3, 0);
        buttonLayout->addWidget(btn2, 3, 1);
        buttonLayout->addWidget(btn3, 3, 2);
        buttonLayout->addWidget(btnAdd, 3, 3);
        
        // 第五行：0 (跨两列) . =
        buttonLayout->addWidget(btn0, 4, 0, 1, 2);  // 跨两列
        buttonLayout->addWidget(btnEquals, 4, 2, 1, 2);  // 跨两列
        
        // 二进制模式按钮（初始隐藏）
        buttonLayout->addWidget(btnA, 5, 0);
        buttonLayout->addWidget(btnB, 5, 1);
        buttonLayout->addWidget(btnC, 5, 2);
        buttonLayout->addWidget(btnD, 5, 3);
        
        buttonLayout->addWidget(btnE, 6, 0);
        buttonLayout->addWidget(btnF, 6, 1);
        buttonLayout->addWidget(btnAnd, 6, 2);
        buttonLayout->addWidget(btnOr, 6, 3);
        
        buttonLayout->addWidget(btnXor, 7, 0);
        buttonLayout->addWidget(btnNot, 7, 1);
        buttonLayout->addWidget(btnLeftShift, 7, 2);
        buttonLayout->addWidget(btnRightShift, 7, 3);
        
        // 进制显示按钮
        buttonLayout->addWidget(btnDecimal, 8, 0);
        buttonLayout->addWidget(btnHex, 8, 1);
        buttonLayout->addWidget(btnBinary, 8, 2, 1, 2);
    }
}

void MainWindow::setupConnections()
{
    // 连接计算引擎信号
    connect(engine, &CalculatorEngine::displayChanged, this, &MainWindow::onDisplayChanged);
    connect(engine, &CalculatorEngine::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(engine, &CalculatorEngine::modeChanged, this, &MainWindow::onModeChanged);
    
    // 连接数字按钮
    connectNumberButton(btn0, "0");
    connectNumberButton(btn1, "1");
    connectNumberButton(btn2, "2");
    connectNumberButton(btn3, "3");
    connectNumberButton(btn4, "4");
    connectNumberButton(btn5, "5");
    connectNumberButton(btn6, "6");
    connectNumberButton(btn7, "7");
    connectNumberButton(btn8, "8");
    connectNumberButton(btn9, "9");
    connectNumberButton(btnA, "A");
    connectNumberButton(btnB, "B");
    connectNumberButton(btnC, "C");
    connectNumberButton(btnD, "D");
    connectNumberButton(btnE, "E");
    connectNumberButton(btnF, "F");
    
    // 连接普通运算符按钮
    connectOperatorButton(btnAdd, "+");
    connectOperatorButton(btnSubtract, "-");
    connectOperatorButton(btnMultiply, "*");
    connectOperatorButton(btnDivide, "/");
    
    // 连接二进制运算符按钮
    connectBinaryOperatorButton(btnAnd, "&");
    connectBinaryOperatorButton(btnOr, "|");
    connectBinaryOperatorButton(btnXor, "^");
    connectBinaryOperatorButton(btnLeftShift, "<<");
    connectBinaryOperatorButton(btnRightShift, ">>");
    
    // NOT 是一元运算符，需要特殊处理
    connect(btnNot, &QPushButton::clicked, this, &MainWindow::onNotClicked);
    
    // 连接功能按钮
    connect(btnEquals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(btnClearEntry, &QPushButton::clicked, this, &MainWindow::onClearEntryClicked);
    connect(btnModeToggle, &QPushButton::clicked, this, &MainWindow::onModeToggleClicked);
    
    // 连接进制显示按钮
    connect(btnDecimal, &QPushButton::clicked, [this]() {
        if (engine->getMode() == CalculatorMode::Binary) {
            display->setText(engine->convertToBase(10));
            updateBaseDisplay();
        }
    });
    
    connect(btnHex, &QPushButton::clicked, [this]() {
        if (engine->getMode() == CalculatorMode::Binary) {
            display->setText(engine->convertToBase(16));
            updateBaseDisplay();
        }
    });
    
    connect(btnBinary, &QPushButton::clicked, [this]() {
        if (engine->getMode() == CalculatorMode::Binary) {
            display->setText(engine->convertToBase(2));
            updateBaseDisplay();
        }
    });
}

void MainWindow::setupStyles()
{
    applyAppleStyle();
}

// 槽函数实现
void MainWindow::onNumberClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString number = button->property("value").toString();
        engine->inputNumber(number);
    }
}

void MainWindow::onOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString op = button->property("operator").toString();
        engine->inputOperator(op);
    }
}

void MainWindow::onBinaryOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString op = button->property("binaryOperator").toString();
        engine->inputBinaryOperator(op);
    }
}

void MainWindow::onNotClicked()
{
    // NOT 是一元运算符，立即对当前值进行运算
    engine->performNotOperation();
}

void MainWindow::onEqualsClicked()
{
    engine->calculate();
}

void MainWindow::onClearClicked()
{
    engine->clear();
}

void MainWindow::onClearEntryClicked()
{
    engine->clearEntry();
}

void MainWindow::onModeToggleClicked()
{
    CalculatorMode currentMode = engine->getMode();
    if (currentMode == CalculatorMode::Normal) {
        engine->setMode(CalculatorMode::Binary);
    } else {
        engine->setMode(CalculatorMode::Normal);
    }
}

void MainWindow::onDisplayChanged(const QString& value)
{
    display->setText(value);
}

void MainWindow::onErrorOccurred(const QString& error)
{
    display->setText(error);
    // 可以添加状态栏显示或其他错误提示
}

void MainWindow::onModeChanged(CalculatorMode mode)
{
    updateModeDisplay();
    updateBaseDisplay();
    updateButtonStates();
}

// 私有方法实现
void MainWindow::updateButtonStates()
{
    CalculatorMode mode = engine->getMode();
    
    if (mode == CalculatorMode::Normal) {
        // 普通模式：显示 0-9，隐藏 A-F 和二进制运算符
        setButtonsVisible({btn0, btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9}, true);
        setButtonsVisible({btnA, btnB, btnC, btnD, btnE, btnF}, false);
        setButtonsVisible({btnAnd, btnOr, btnXor, btnNot, btnLeftShift, btnRightShift}, false);
        setButtonsVisible({btnAdd, btnSubtract, btnMultiply, btnDivide}, true);
        setButtonsVisible({btnDecimal, btnHex, btnBinary}, false);
        
        btnModeToggle->setText("BIN");
        
    } else {
        // 二进制模式：显示 0-1，显示 A-F 和二进制运算符
        setButtonsVisible({btn0, btn1}, true);
        setButtonsVisible({btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9}, false);
        setButtonsVisible({btnA, btnB, btnC, btnD, btnE, btnF}, true);
        setButtonsVisible({btnAnd, btnOr, btnXor, btnNot, btnLeftShift, btnRightShift}, true);
        setButtonsVisible({btnAdd, btnSubtract, btnMultiply, btnDivide}, true);
        setButtonsVisible({btnDecimal, btnHex, btnBinary}, true);
        
        btnModeToggle->setText("DEC");
    }
}

void MainWindow::updateModeDisplay()
{
    CalculatorMode mode = engine->getMode();
    if (mode == CalculatorMode::Normal) {
        modeLabel->setText("普通");
    } else {
        modeLabel->setText("二进制");
    }
}

void MainWindow::updateBaseDisplay()
{
    CalculatorMode mode = engine->getMode();
    if (mode == CalculatorMode::Normal) {
        baseLabel->setText("DEC");
    } else {
        baseLabel->setText("BIN");
    }
}

void MainWindow::applyAppleStyle()
{
    // 应用 Apple 风格样式表
    QString numberButtonStyle = getButtonStyle("number");
    QString operatorButtonStyle = getButtonStyle("operator");
    QString functionButtonStyle = getButtonStyle("function");
    
    // 应用数字按钮样式
    QList<QPushButton*> numberBtns = {btn0, btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btnA, btnB, btnC, btnD, btnE, btnF};
    for (QPushButton* btn : numberBtns) {
        btn->setStyleSheet(numberButtonStyle);
        btn->setMinimumSize(80, 60);
    }
    
    // 应用运算符按钮样式
    QList<QPushButton*> operatorBtns = {btnAdd, btnSubtract, btnMultiply, btnDivide};
    for (QPushButton* btn : operatorBtns) {
        btn->setStyleSheet(operatorButtonStyle);
        btn->setMinimumSize(80, 60);
    }
    
    // 应用二进制运算符按钮样式
    QList<QPushButton*> binaryOperatorBtns = {btnAnd, btnOr, btnXor, btnNot, btnLeftShift, btnRightShift};
    for (QPushButton* btn : binaryOperatorBtns) {
        btn->setStyleSheet(operatorButtonStyle);
        btn->setMinimumSize(80, 60);
    }
    
    // 应用功能按钮样式
    btnEquals->setStyleSheet(operatorButtonStyle);
    btnEquals->setMinimumSize(80, 60);
    
    // 进制显示按钮
    QList<QPushButton*> baseBtns = {btnDecimal, btnHex, btnBinary};
    for (QPushButton* btn : baseBtns) {
        btn->setStyleSheet(functionButtonStyle);
        btn->setMinimumSize(80, 40);
    }
}

QString MainWindow::getButtonStyle(const QString& type) const
{
    if (type == "number") {
        return R"(
            QPushButton {
                background-color: #ffffff;
                color: #333333;
                border: none;
                border-radius: 8px;
                font-size: 24px;
                font-weight: 400;
            }
            QPushButton:hover {
                background-color: #f0f0f0;
            }
            QPushButton:pressed {
                background-color: #e0e0e0;
            }
        )";
    } else if (type == "operator") {
        return R"(
            QPushButton {
                background-color: #ff9500;
                color: #ffffff;
                border: none;
                border-radius: 8px;
                font-size: 24px;
                font-weight: 400;
            }
            QPushButton:hover {
                background-color: #ffad33;
            }
            QPushButton:pressed {
                background-color: #e6850e;
            }
        )";
    } else if (type == "function") {
        return R"(
            QPushButton {
                background-color: #a6a6a6;
                color: #ffffff;
                border: none;
                border-radius: 8px;
                font-size: 18px;
                font-weight: 500;
            }
            QPushButton:hover {
                background-color: #b8b8b8;
            }
            QPushButton:pressed {
                background-color: #949494;
            }
        )";
    }
    return "";
}

QString MainWindow::getDisplayStyle() const
{
    return R"(
        QLineEdit {
            background-color: transparent;
            border: none;
            color: #ffffff;
            font-size: 36px;
            font-weight: 300;
            padding: 0px;
        }
    )";
}

QString MainWindow::getWindowStyle() const
{
    return R"(
        QMainWindow {
            background-color: #f0f0f0;
        }
        QWidget {
            font-family: "SF Pro Display", "Segoe UI", "Arial";
        }
    )";
}

void MainWindow::setButtonsEnabled(const QList<QPushButton*>& buttons, bool enabled)
{
    for (QPushButton* button : buttons) {
        button->setEnabled(enabled);
    }
}

void MainWindow::setButtonsVisible(const QList<QPushButton*>& buttons, bool visible)
{
    for (QPushButton* button : buttons) {
        button->setVisible(visible);
    }
}

QPushButton* MainWindow::createButton(const QString& text, const QString& objectName)
{
    QPushButton* button = new QPushButton(text, this);
    if (!objectName.isEmpty()) {
        button->setObjectName(objectName);
    }
    button->setMinimumSize(80, 60);
    return button;
}

void MainWindow::connectNumberButton(QPushButton* button, const QString& value)
{
    button->setProperty("value", value);
    connect(button, &QPushButton::clicked, this, &MainWindow::onNumberClicked);
}

void MainWindow::connectOperatorButton(QPushButton* button, const QString& op)
{
    button->setProperty("operator", op);
    connect(button, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
}

void MainWindow::connectBinaryOperatorButton(QPushButton* button, const QString& op)
{
    button->setProperty("binaryOperator", op);
    connect(button, &QPushButton::clicked, this, &MainWindow::onBinaryOperatorClicked);
} 