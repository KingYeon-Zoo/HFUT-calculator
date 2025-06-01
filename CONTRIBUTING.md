# 贡献指南 Contributing Guide

感谢您对HFUT Calculator项目的关注！我们欢迎所有形式的贡献，包括但不限于代码、文档、测试、问题报告和功能建议。

## 如何贡献

### 1. 报告问题 (Bug Reports)

如果您发现了bug，请：
- 首先检查[现有issues](../../issues)，确保问题未被报告
- 使用提供的[Bug报告模板](../../issues/new?template=bug_report.md)
- 提供详细的重现步骤
- 包含您的系统信息（操作系统、Qt版本、编译器版本）

### 2. 功能请求 (Feature Requests)

如果您有新功能建议：
- 检查[现有issues](../../issues)，避免重复请求
- 使用[功能请求模板](../../issues/new?template=feature_request.md)
- 详细描述您的需求和使用场景
- 考虑提供实现方案的初步想法

### 3. 提交代码 (Pull Requests)

#### 准备工作
1. Fork这个仓库
2. 创建您的功能分支：`git checkout -b feature/your-feature-name`
3. 确保您的开发环境符合要求：
   - Qt 5.15+ 或 Qt 6.x
   - C++17 兼容的编译器
   - 推荐使用Qt Creator

#### 代码规范
- **C++代码风格**：
  - 使用4个空格缩进
  - 变量和函数使用camelCase命名
  - 类名使用PascalCase命名
  - 常量使用UPPER_CASE命名
  - 头文件使用`#pragma once`而不是`#ifndef`

- **提交消息规范**：
  ```
  类型(作用域): 简短描述
  
  详细描述（可选）
  
  类型包括：
  - feat: 新功能
  - fix: bug修复
  - docs: 文档更新
  - style: 代码格式调整
  - refactor: 重构
  - test: 测试相关
  - chore: 构建或工具相关
  ```

#### 代码质量要求
1. **编译要求**：
   - 代码必须在Windows、Linux、macOS上编译通过
   - 不能有编译警告
   - 使用现代C++17特性

2. **功能要求**：
   - 新功能必须包含适当的错误处理
   - 保持与现有UI风格的一致性
   - 确保在普通模式和二进制模式下都能正常工作

3. **测试要求**：
   - 手动测试所有相关功能
   - 确保不破坏现有功能
   - 在多个平台上验证（如果可能）

#### 提交流程
1. 确保您的代码符合上述要求
2. 提交您的更改：`git commit -m "feat: 添加新的计算功能"`
3. 推送到您的分支：`git push origin feature/your-feature-name`
4. 创建Pull Request
5. 使用提供的[PR模板](../../pulls)填写详细信息

### 4. 改进文档

文档改进同样重要：
- 修正README中的错误或不准确信息
- 添加更多使用示例
- 改进代码注释
- 翻译文档到其他语言

## 开发环境设置

### 快速开始
1. 克隆仓库：
   ```bash
   git clone https://github.com/kingyeon-zoo/HFUT-calculator.git
   cd HFUT-calculator
   ```

2. 使用Qt Creator打开`HFUT-calculator.pro`

3. 配置构建套件并编译

### 命令行编译
```bash
mkdir build && cd build
qmake ../HFUT-calculator.pro
make  # 或 mingw32-make (Windows)
```

## 项目结构

```
HFUT-calculator/
├── main.cpp                    # 程序入口
├── calculatorengine.{h,cpp}    # 计算引擎
├── mainwindow.{h,cpp,ui}       # 主界面
├── build.{sh,bat}              # 构建脚本
├── HFUT-calculator.pro         # Qt项目文件
└── docs/                       # 文档目录
```

## 发布版本

版本发布由维护者负责，遵循[语义化版本](https://semver.org/)规范：
- `主版本.次版本.修订版本`
- 主版本：不兼容的API更改
- 次版本：向后兼容的功能新增
- 修订版本：向后兼容的问题修正

## 社区行为准则

请始终保持友善和专业：
- 尊重不同观点和经验
- 优雅地接受建设性批评
- 专注于对社区最有利的事情
- 对其他社区成员表现出同理心

## 获得帮助

如果您在贡献过程中遇到问题：
1. 查看现有的[issues和讨论](../../issues)
2. 创建新的issue寻求帮助
3. 确保提供足够的上下文信息

## 许可证

通过贡献代码，您同意您的贡献将在MIT许可证下发布。

---

再次感谢您的贡献！每一个贡献都让HFUT Calculator变得更好。 
