#include "calculatorengine.h"
#include <QDebug>
#include <cmath>
#include <limits>

CalculatorEngine::CalculatorEngine(QObject *parent)
    : QObject(parent)
    , currentMode(CalculatorMode::Normal)
    , currentState(CalculatorState::WaitingForOperand)
    , currentValue(0.0)
    , storedValue(0.0)
    , currentOperator("")
    , displayText("0")
    , expressionText("")
    , hasError(false)
    , errorMessage("")
{
}

void CalculatorEngine::setMode(CalculatorMode mode)
{
    if (currentMode != mode) {
        currentMode = mode;
        clear(); // 切换模式时清空状态
        emit modeChanged(mode);
    }
}

CalculatorMode CalculatorEngine::getMode() const
{
    return currentMode;
}

void CalculatorEngine::inputNumber(const QString& number)
{
    if (hasError) {
        clear();
    }
    
    try {
        // 验证输入
        if (currentMode == CalculatorMode::Binary && !isValidBinaryNumber(number)) {
            throw InvalidOperationException("二进制模式下只能输入0和1");
        }
        
        if (currentMode == CalculatorMode::Normal && !isValidNumber(number)) {
            throw InvalidOperationException("无效的数字输入");
        }
        
        // 处理输入
        if (currentState == CalculatorState::WaitingForOperand || displayText == "0") {
            displayText = number;
            if (expressionText.isEmpty() || expressionText.endsWith(" ")) {
                expressionText += number;
            } else {
                expressionText = number;  // 新的计算开始
            }
            currentState = CalculatorState::WaitingForOperator;
        } else {
            if (currentState == CalculatorState::WaitingForOperator) {
                displayText += number;
                expressionText += number;
            }
        }
        
        // 更新当前值
        if (currentMode == CalculatorMode::Binary) {
            currentValue = static_cast<double>(displayText.toLongLong(nullptr, 2));
        } else {
            currentValue = displayText.toDouble();
        }
        
        updateDisplay();
        
    } catch (const CalculatorException& e) {
        setError(e.getMessage());
    }
}

void CalculatorEngine::inputOperator(const QString& op)
{
    if (hasError) {
        return;
    }
    
    try {
        // 验证运算符
        if (currentMode == CalculatorMode::Normal && !isValidOperator(op)) {
            throw InvalidOperationException("无效的运算符");
        }
        
        if (currentMode == CalculatorMode::Binary && !isValidBinaryOperator(op)) {
            throw InvalidOperationException("二进制模式下无效的运算符");
        }
        
        // 如果已有运算符且等待操作数，先计算
        if (!currentOperator.isEmpty() && currentState == CalculatorState::WaitingForOperator) {
            calculate();
        }
        
        storedValue = currentValue;
        currentOperator = op;
        currentState = CalculatorState::WaitingForOperand;
        
        // 更新表达式显示
        expressionText += " " + op + " ";
        
    } catch (const CalculatorException& e) {
        setError(e.getMessage());
    }
}

QString CalculatorEngine::calculate()
{
    if (hasError || currentOperator.isEmpty()) {
        return displayText;
    }
    
    try {
        double result;
        
        if (currentMode == CalculatorMode::Binary) {
            long long leftOperand = static_cast<long long>(storedValue);
            long long rightOperand = static_cast<long long>(currentValue);
            long long binaryResult = performBinaryCalculation(leftOperand, currentOperator, rightOperand);
            result = static_cast<double>(binaryResult);
        } else {
            result = performCalculation(storedValue, currentOperator, currentValue);
        }
        
        // 检查溢出
        if (std::isinf(result) || std::isnan(result)) {
            throw OverflowException();
        }
        
        currentValue = result;
        currentOperator.clear();
        currentState = CalculatorState::WaitingForOperand;
        
        // 更新显示
        QString resultText;
        if (currentMode == CalculatorMode::Binary) {
            resultText = longLongToString(static_cast<long long>(result), 2);
        } else {
            resultText = doubleToString(result);
        }
        
        // 显示完整表达式和结果
        expressionText += " = " + resultText;
        displayText = expressionText;
        
        updateDisplay();
        return resultText;
        
    } catch (const CalculatorException& e) {
        setError(e.getMessage());
        return errorMessage;
    }
}

void CalculatorEngine::clear()
{
    currentValue = 0.0;
    storedValue = 0.0;
    currentOperator.clear();
    displayText = "0";
    expressionText.clear();
    currentState = CalculatorState::WaitingForOperand;
    hasError = false;
    errorMessage.clear();
    updateDisplay();
}

void CalculatorEngine::clearEntry()
{
    if (!hasError) {
        displayText = "0";
        expressionText.clear();
        currentValue = 0.0;
        if (currentState == CalculatorState::WaitingForOperator) {
            currentState = CalculatorState::WaitingForOperand;
        }
        updateDisplay();
    }
}

QString CalculatorEngine::getDisplayValue() const
{
    if (hasError) {
        return errorMessage;
    }
    
    // 如果有表达式且不为空，显示表达式，否则显示当前值
    if (!expressionText.isEmpty() && !expressionText.contains("=")) {
        return expressionText;
    } else {
        return displayText;
    }
}

bool CalculatorEngine::isWaitingForOperand() const
{
    return currentState == CalculatorState::WaitingForOperand;
}

QString CalculatorEngine::convertToBase(int base) const
{
    if (hasError || currentMode != CalculatorMode::Binary) {
        return displayText;
    }
    
    long long value = static_cast<long long>(currentValue);
    return longLongToString(value, base);
}

void CalculatorEngine::inputBinaryOperator(const QString& op)
{
    inputOperator(op);
}

void CalculatorEngine::performNotOperation()
{
    if (hasError) {
        return;
    }
    
    try {
        if (currentMode != CalculatorMode::Binary) {
            throw InvalidOperationException("NOT 运算只能在二进制模式下使用");
        }
        
        // 获取当前显示的二进制字符串
        QString binaryStr;
        if (!expressionText.isEmpty() && !expressionText.contains("=")) {
            binaryStr = expressionText;
        } else {
            // 如果当前值是从十进制转换来的，先转换为二进制字符串
            long long currentIntValue = static_cast<long long>(currentValue);
            binaryStr = longLongToString(currentIntValue, 2);
        }
        
        // 对二进制字符串的每一位进行取反
        QString resultStr = "";
        for (const QChar& bit : binaryStr) {
            if (bit == '0') {
                resultStr += '1';
            } else if (bit == '1') {
                resultStr += '0';
            }
        }
        
        // 转换回数值
        bool ok;
        long long result = resultStr.toLongLong(&ok, 2);
        if (!ok) {
            throw InvalidOperationException("NOT 运算结果无效");
        }
        
        // 更新当前值和显示
        currentValue = static_cast<double>(result);
        
        // 更新表达式和显示
        if (!expressionText.isEmpty() && !expressionText.contains("=")) {
            expressionText = "NOT(" + expressionText + ") = " + resultStr;
        } else {
            expressionText = "NOT(" + binaryStr + ") = " + resultStr;
        }
        displayText = expressionText;
        
        // 重置状态，准备下一次输入
        currentState = CalculatorState::WaitingForOperand;
        
        updateDisplay();
        
    } catch (const CalculatorException& e) {
        setError(e.getMessage());
    }
}

// 私有方法实现
double CalculatorEngine::performCalculation(double left, const QString& op, double right)
{
    if (op == "+") {
        return left + right;
    } else if (op == "-") {
        return left - right;
    } else if (op == "*") {
        return left * right;
    } else if (op == "/") {
        if (std::abs(right) < std::numeric_limits<double>::epsilon()) {
            throw DivisionByZeroException();
        }
        return left / right;
    }
    
    throw InvalidOperationException("未知运算符: " + op);
}

long long CalculatorEngine::performBinaryCalculation(long long left, const QString& op, long long right)
{
    if (op == "&") {
        return left & right;
    } else if (op == "|") {
        return left | right;
    } else if (op == "^") {
        return left ^ right;
    } else if (op == "<<") {
        if (right < 0 || right > 63) {
            throw InvalidOperationException("位移量超出范围");
        }
        return left << right;
    } else if (op == ">>") {
        if (right < 0 || right > 63) {
            throw InvalidOperationException("位移量超出范围");
        }
        return left >> right;
    } else if (op == "+") {
        return left + right;
    } else if (op == "-") {
        return left - right;
    } else if (op == "*") {
        return left * right;
    } else if (op == "/") {
        if (right == 0) {
            throw DivisionByZeroException();
        }
        return left / right;
    }
    
    throw InvalidOperationException("未知二进制运算符: " + op);
}

bool CalculatorEngine::isValidNumber(const QString& number) const
{
    bool ok;
    number.toDouble(&ok);
    return ok;
}

bool CalculatorEngine::isValidBinaryNumber(const QString& number) const
{
    for (const QChar& ch : number) {
        if (ch != '0' && ch != '1') {
            return false;
        }
    }
    return !number.isEmpty();
}

bool CalculatorEngine::isValidOperator(const QString& op) const
{
    return op == "+" || op == "-" || op == "*" || op == "/";
}

bool CalculatorEngine::isValidBinaryOperator(const QString& op) const
{
    return op == "+" || op == "-" || op == "*" || op == "/" ||
           op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>";
}

void CalculatorEngine::updateDisplay()
{
    emit displayChanged(getDisplayValue());
}

void CalculatorEngine::setError(const QString& error)
{
    hasError = true;
    errorMessage = error;
    emit errorOccurred(error);
    updateDisplay();
}

void CalculatorEngine::resetState()
{
    currentState = CalculatorState::WaitingForOperand;
    currentOperator.clear();
}

QString CalculatorEngine::doubleToString(double value) const
{
    // 移除不必要的小数点和尾随零
    QString result = QString::number(value, 'g', 15);
    return result;
}

QString CalculatorEngine::longLongToString(long long value, int base) const
{
    return QString::number(value, base).toUpper();
}

 