# 变更日志 Changelog

本文档记录了HFUT Calculator项目的所有重要变更。

格式基于 [Keep a Changelog](https://keepachangelog.com/zh-CN/1.0.0/)，
并且本项目遵循 [语义化版本](https://semver.org/lang/zh-CN/)。

## [未发布] - Unreleased

### 新增 Added
- 开源项目配置：添加了完整的GitHub开源文件集
- `.gitignore` 文件：针对Qt C++项目优化的忽略规则
- MIT许可证
- 贡献指南和GitHub模板
- 项目变更日志

### 变更 Changed
- README.md：更新为开源项目标准格式

### 已移除 Removed
- 清理了编译产物和临时文件

## [1.0.0] 

### 新增 Added
- 双模式计算器核心功能
  - 普通模式：支持基本四则运算（+、-、×、÷）
  - 二进制模式：支持位运算（AND、OR、XOR、左移、右移）
- Apple风格现代化UI设计
  - 圆角按钮和优雅配色
  - 黑色显示屏配白色文字
  - 响应式布局
- 完整的异常处理机制
  - 除零错误检测
  - 数值溢出保护
  - 无效输入验证
  - 用户友好的错误提示
- 模式切换功能
  - 一键切换普通/二进制模式
  - 动态按钮显示/隐藏
  - 自动界面状态更新
- 跨平台支持
  - Windows (MinGW/MSVC)
  - Linux (GCC/Clang)
  - macOS (Xcode)
- 构建系统
  - qmake项目配置
  - 跨平台构建脚本 (build.sh/build.bat)
  - Qt Creator集成

### 技术特性 Technical Features
- C++17 标准
- Qt Widgets 框架
- 模块化代码架构
  - `CalculatorEngine` 类：独立的计算逻辑
  - `MainWindow` 类：UI交互和界面管理
- 完整的错误处理和输入验证

---

## 版本规范说明

### 版本号格式
我们使用语义化版本控制 (SemVer)：`主版本.次版本.修订版本`

- **主版本**：不兼容的API修改
- **次版本**：向后兼容的功能新增
- **修订版本**：向后兼容的问题修正

### 变更类型

- **新增 Added**：新功能
- **变更 Changed**：现有功能的变更
- **已弃用 Deprecated**：即将移除的功能
- **已移除 Removed**：已删除的功能
- **修复 Fixed**：bug修复
- **安全 Security**：安全相关的修复

### 发布说明

每个发布版本都会在GitHub Releases中提供：
- 变更摘要
- 下载链接
- 系统要求
- 安装说明

---

**注意**：此变更日志从项目开源化开始维护。如需了解更早期的开发历史，请查看git提交记录。 
