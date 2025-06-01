# HFUT Calculator

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Qt](https://img.shields.io/badge/Qt-5.15%2B%20%7C%206.x-green.svg)](https://www.qt.io/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-blue.svg)](https://github.com/your-username/HFUT-calculator)
[![C++](https://img.shields.io/badge/C%2B%2B-17-red.svg)](https://en.cppreference.com/w/cpp/17)

一个基于 Qt 框架的双模式计算器应用程序，具有现代化的 Apple 风格 UI 设计。

## 功能特性

### 🧮 双模式计算器
- **普通模式**: 支持基本的四则运算（加、减、乘、除）
- **二进制模式**: 支持位运算（AND、OR、XOR、左移、右移）

### 🎨 Apple 风格 UI
- 现代化的界面设计
- 圆角按钮和优雅配色
- 黑色显示屏配白色文字
- 响应式布局设计

### 🛡️ 异常处理
- 除零错误检测
- 数值溢出保护
- 无效输入验证
- 用户友好的错误提示

### 🔄 模式切换
- 一键切换普通/二进制模式
- 动态按钮显示/隐藏
- 自动界面状态更新

## 系统要求

### 必需软件
1. **Qt 开发环境** (Qt 5.15+ 或 Qt 6.x)
   - Qt Creator IDE
   - Qt Widgets 模块
   - qmake 构建工具

2. **C++ 编译器**
   - Windows: MinGW 或 MSVC
   - Linux: GCC 或 Clang
   - macOS: Xcode Command Line Tools

### 推荐安装方式

#### Windows 用户
1. 下载并安装 [Qt Creator](https://www.qt.io/download-qt-installer)
2. 在安装过程中选择：
   - Qt 6.x 或 Qt 5.15+
   - MinGW 13.1.0+ 编译器（推荐）
   - Qt Creator IDE

**重要提示**: 如果使用 Qt 6.9.0，请确保使用 MinGW 13.1.0 或更高版本的编译器。旧版本的 MinGW (如 8.1.0) 与 Qt 6.9.0 存在兼容性问题。

#### Linux 用户 (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev build-essential
# 或者对于 Qt5
sudo apt install qt5-default qttools5-dev-tools build-essential
```

#### macOS 用户
```bash
# 使用 Homebrew
brew install qt
# 或者下载 Qt Creator 安装包
```

## 编译和运行

### 方法一：使用 Qt Creator (推荐)
1. 打开 Qt Creator
2. 选择 "Open Project"
3. 打开 `HFUT-calculator.pro` 文件
4. 配置构建套件（Kit）
5. 点击 "Build" 按钮编译
6. 点击 "Run" 按钮运行

### 方法二：命令行编译
确保 qmake 在系统 PATH 中，然后执行：

#### Windows
```cmd
build.bat
```

#### Linux/macOS
```bash
chmod +x build.sh
./build.sh
```

#### 手动编译
```bash
mkdir build
cd build
qmake ../HFUT-calculator.pro
make          # Linux/macOS
# 或
mingw32-make  # Windows MinGW
```

## 项目结构

```
HFUT-calculator/
├── HFUT-calculator.pro     # Qt 项目配置文件
├── main.cpp                # 程序入口点
├── calculatorengine.h      # 计算引擎头文件
├── calculatorengine.cpp    # 计算引擎实现
├── mainwindow.h            # 主窗口头文件
├── mainwindow.cpp          # 主窗口实现
├── mainwindow.ui           # Qt Designer 界面文件
├── build.bat               # Windows 编译脚本
├── build.sh                # Linux/macOS 编译脚本
└── README.md               # 项目说明文档
```

## 使用说明

### 普通模式
- 点击数字按钮 (0-9) 输入数字
- 点击运算符按钮 (+, -, ×, ÷) 选择运算
- 点击 "=" 按钮计算结果
- 点击 "C" 清空所有内容
- 点击 "CE" 清空当前输入

### 二进制模式
- 点击 "BIN" 按钮切换到二进制模式
- 只能输入 0 和 1
- 支持位运算：AND, OR, XOR, 左移(<<), 右移(>>)
- 支持进制转换：DEC (十进制), HEX (十六进制), BIN (二进制)
- 点击 "DEC" 按钮切换回普通模式

## 故障排除

### 编译错误
1. **"qmake: command not found"**
   - 确保已安装 Qt 开发环境
   - 检查 qmake 是否在系统 PATH 中
   - 尝试使用 Qt Creator 打开项目

2. **"No rule to make target 'moc'"**
   - 清理构建缓存：删除 build 目录和 .pro.user 文件
   - 重新运行 qmake 和 make

3. **编译器兼容性错误**
   - 如果遇到 "static assertion failed" 等错误，通常是编译器版本过旧
   - Windows: 确保使用 MinGW 13.1.0+ 而不是 8.1.0
   - Linux: 确保使用 GCC 9+ 或 Clang 10+
   - 更新编译器或使用 Qt Creator 的内置编译器

4. **缺少 Qt 模块**
   - 确保安装了 Qt Widgets 模块
   - 检查 Qt 版本兼容性

### 运行时错误
1. **应用程序无法启动**
   - 确保 Qt 运行时库在系统 PATH 中
   - 检查是否缺少 DLL 文件

## 开发信息

- **开发语言**: C++17
- **UI 框架**: Qt Widgets
- **构建系统**: qmake
- **设计风格**: Apple Inc. 风格
- **许可证**: MIT License

## 贡献 Contributing

我们欢迎所有形式的贡献！请查看 [贡献指南](CONTRIBUTING.md) 了解详细信息。

### 快速开始贡献
1. Fork 这个仓库
2. 创建您的功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交您的更改 (`git commit -m 'feat: 添加某个新功能'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建一个 Pull Request

### 报告问题
如果您发现bug或有功能建议，请：
- 查看 [现有 Issues](../../issues)
- 创建 [新的 Bug 报告](../../issues/new?template=bug_report.md)
- 创建 [功能请求](../../issues/new?template=feature_request.md)

## 许可证 License

本项目基于 MIT 许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 致谢 Acknowledgments

- 感谢 Qt 框架提供的强大UI工具
- 灵感来源于 Apple Calculator 的简洁设计
- 感谢所有贡献者的支持和建议

## 联系方式 Contact

如有问题或建议，请通过以下方式联系：
- 创建 [GitHub Issue](../../issues)
- 项目维护者: [Chinyen Zoo](https://github.com/kingyeon-zoo)

## 变更日志 Changelog

查看 [CHANGELOG.md](CHANGELOG.md) 了解详细的版本历史和更新内容。 
