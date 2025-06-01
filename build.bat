@echo off
echo ========================================
echo HFUT Calculator 构建脚本 (Windows)
echo ========================================

REM 设置 Qt 和 MinGW 路径
set QT_DIR=D:\Qt\6.9.0\mingw_64
set MINGW_DIR=D:\Qt\Tools\mingw1310_64
set PATH=%MINGW_DIR%\bin;%QT_DIR%\bin;%PATH%

REM 检查 qmake 是否可用
where qmake >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo 错误: 未找到 qmake 命令
    echo 请确保已安装 Qt 开发环境并正确设置了路径
    echo 预期路径: %QT_DIR%\bin\qmake.exe
    pause
    exit /b 1
)

REM 检查 MinGW 编译器是否可用
where gcc >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo 错误: 未找到 gcc 编译器
    echo 请确保已安装 MinGW 编译器并正确设置了路径
    echo 预期路径: %MINGW_DIR%\bin\gcc.exe
    pause
    exit /b 1
)

echo 使用的编译器版本:
gcc --version | findstr "gcc"

echo.
echo 清理旧的构建文件...
if exist build rmdir /s /q build
if exist bin rmdir /s /q bin

echo 创建构建目录...
mkdir build
cd build

echo.
echo 生成 Makefile...
qmake ..\HFUT-calculator.pro
if %ERRORLEVEL% neq 0 (
    echo 错误: qmake 执行失败
    cd ..
    pause
    exit /b 1
)

echo.
echo 开始编译...
mingw32-make
if %ERRORLEVEL% neq 0 (
    echo 错误: 编译失败
    cd ..
    pause
    exit /b 1
)

cd ..

echo.
echo ========================================
echo 构建成功完成！
echo ========================================
echo 可执行文件位置: bin\HFUT-calculator.exe
echo.
echo 要运行程序，请执行:
echo cd bin
echo HFUT-calculator.exe
echo.
pause 