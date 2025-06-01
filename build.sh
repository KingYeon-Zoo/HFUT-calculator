#!/bin/bash

echo "========================================"
echo "HFUT Calculator 构建脚本 (Linux/macOS)"
echo "========================================"

# 检查 qmake 是否可用
if ! command -v qmake &> /dev/null; then
    echo "错误: 未找到 qmake 命令"
    echo "请安装 Qt 开发环境:"
    echo ""
    echo "Ubuntu/Debian:"
    echo "  sudo apt update"
    echo "  sudo apt install qt6-base-dev qt6-tools-dev build-essential"
    echo ""
    echo "macOS (使用 Homebrew):"
    echo "  brew install qt"
    echo ""
    echo "或者下载并安装 Qt Creator: https://www.qt.io/download-qt-installer"
    exit 1
fi

# 检查编译器是否可用
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "错误: 未找到 C++ 编译器 (g++ 或 clang++)"
    echo "请安装编译器:"
    echo ""
    echo "Ubuntu/Debian:"
    echo "  sudo apt install build-essential"
    echo ""
    echo "macOS:"
    echo "  xcode-select --install"
    exit 1
fi

echo "使用的 qmake 版本:"
qmake --version

echo ""
echo "清理旧的构建文件..."
rm -rf build bin *.pro.user

echo "创建构建目录..."
mkdir -p build
cd build

echo ""
echo "生成 Makefile..."
qmake ../HFUT-calculator.pro

if [ $? -ne 0 ]; then
    echo "错误: qmake 执行失败"
    cd ..
    exit 1
fi

echo ""
echo "开始编译..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    cd ..
    echo ""
    echo "========================================"
    echo "构建成功完成！"
    echo "========================================"
    echo "可执行文件位置: bin/HFUT-calculator"
    echo ""
    echo "要运行程序，请执行:"
    echo "cd bin"
    echo "./HFUT-calculator"
    echo ""
else
    echo ""
    echo "========================================"
    echo "编译失败，请检查错误信息"
    echo "========================================"
    echo ""
    echo "常见解决方案:"
    echo "1. 确保已安装完整的 Qt 开发环境"
    echo "2. 检查是否缺少依赖库"
    echo "3. 尝试使用 Qt Creator 打开项目进行编译"
    echo ""
    cd ..
    exit 1
fi 