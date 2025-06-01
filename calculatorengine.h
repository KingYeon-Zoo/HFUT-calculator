#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QString>
#include <QObject>
#include <stdexcept>

// 计算器模式枚举
enum class CalculatorMode {
    Normal,    // 普通计算器模式
    Binary     // 二进制计算器模式
};

// 计算器状态枚举
enum class CalculatorState {
    WaitingForOperand,    // 等待操作数
    WaitingForOperator    // 等待运算符
};

// 自定义异常类
class CalculatorException : public std::exception {
private:
    QString message;
public:
    explicit CalculatorException(const QString& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.toLocal8Bit().constData();
    }
    QString getMessage() const { return message; }
};

class DivisionByZeroException : public CalculatorException {
public:
    DivisionByZeroException() : CalculatorException("除零错误") {}
};

class OverflowException : public CalculatorException {
public:
    OverflowException() : CalculatorException("数值溢出") {}
};

class InvalidOperationException : public CalculatorException {
public:
    InvalidOperationException(const QString& msg) : CalculatorException("无效操作: " + msg) {}
};

// 计算引擎类
class CalculatorEngine : public QObject
{
    Q_OBJECT

public:
    explicit CalculatorEngine(QObject *parent = nullptr);
    
    // 主要接口方法
    void setMode(CalculatorMode mode);
    CalculatorMode getMode() const;
    
    void inputNumber(const QString& number);
    void inputOperator(const QString& op);
    QString calculate();
    void clear();
    void clearEntry();
    
    QString getDisplayValue() const;
    bool isWaitingForOperand() const;
    
    // 二进制模式特有方法
    QString convertToBase(int base) const;  // 转换为指定进制显示
    void inputBinaryOperator(const QString& op);
    void performNotOperation();  // 执行 NOT 一元运算
    
signals:
    void displayChanged(const QString& value);
    void errorOccurred(const QString& error);
    void modeChanged(CalculatorMode mode);

private:
    // 私有成员变量
    CalculatorMode currentMode;
    CalculatorState currentState;
    
    double currentValue;      // 当前显示值
    double storedValue;       // 存储的操作数
    QString currentOperator;  // 当前运算符
    QString displayText;      // 显示文本
    QString expressionText;   // 表达式文本（显示完整输入）
    
    bool hasError;           // 错误状态标志
    QString errorMessage;    // 错误信息
    
    // 私有辅助方法
    double performCalculation(double left, const QString& op, double right);
    long long performBinaryCalculation(long long left, const QString& op, long long right);
    
    bool isValidNumber(const QString& number) const;
    bool isValidBinaryNumber(const QString& number) const;
    bool isValidOperator(const QString& op) const;
    bool isValidBinaryOperator(const QString& op) const;
    
    void updateDisplay();
    void setError(const QString& error);
    void resetState();
    
    // 数值转换辅助方法
    QString doubleToString(double value) const;
    QString longLongToString(long long value, int base = 10) const;
};

#endif // CALCULATORENGINE_H 