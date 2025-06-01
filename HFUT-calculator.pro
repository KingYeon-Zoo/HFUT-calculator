QT += core widgets

CONFIG += c++17

TARGET = HFUT-calculator
TEMPLATE = app

# 源文件
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    calculatorengine.cpp

# 头文件
HEADERS += \
    mainwindow.h \
    calculatorengine.h

# UI 文件
FORMS += \
    mainwindow.ui

# 设置应用程序图标和版本信息
VERSION = 1.0.0
QMAKE_TARGET_COMPANY = "HFUT"
QMAKE_TARGET_PRODUCT = "HFUT Calculator"
QMAKE_TARGET_DESCRIPTION = "A dual-mode calculator with Apple-style UI"

# 编译选项
QMAKE_CXXFLAGS += -Wall -Wextra

# Windows 特定设置
win32 {
    # RC_ICONS = icon.ico  # 暂时注释掉图标，避免编译错误
}

# macOS 特定设置
macx {
    # ICON = icon.icns  # 暂时注释掉图标，避免编译错误
}

# 输出目录
DESTDIR = $$PWD/bin 