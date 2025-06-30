# 二叉树工程

这是一个使用Bazel构建的二叉树实现项目，包含完整的测试用例和覆盖率报告功能。

## 项目结构

```
coverage/
├── WORKSPACE                 # Bazel工作空间配置
├── src/
│   ├── binary_tree.h         # 二叉树实现头文件
│   └── BUILD                 # 源码构建配置
├── test/
│   ├── binary_tree_test.cc   # GTest测试用例
│   └── BUILD                 # 测试构建配置
├── examples/
│   ├── binary_tree_example.cc # 使用示例
│   └── BUILD                 # 示例构建配置
├── scripts/
│   └── run_coverage.sh       # 覆盖率运行脚本
├── third_party/
│   └── gcovr.BUILD          # Gcovr构建配置
└── README.md                # 项目说明
```

## 功能特性

### 二叉树实现
- 支持插入、删除、搜索操作
- 三种遍历方式：中序、前序、后序
- 树属性查询：高度、深度、大小、最小值、最大值
- 树验证：平衡性检查、BST验证

### 测试覆盖
- 使用Google Test框架
- 全面的单元测试用例
- 支持函数、行、分支覆盖率报告

## 构建和运行

### 环境要求
- Bazel 5.0+
- GCC/Clang编译器
- Python 3.6+ (用于gcovr)

### 构建项目
```bash
# 构建所有目标
bazel build //...

# 构建示例程序
bazel build //examples:binary_tree_example

# 构建测试
bazel build //test:binary_tree_test
```

### 运行测试
```bash
# 运行所有测试
bazel test //test:binary_tree_test

# 运行测试并显示详细输出
bazel test //test:binary_tree_test --test_output=all
```

### 运行示例程序
```bash
# 运行示例程序
bazel run //examples:binary_tree_example
```

## 覆盖率测试

### 生成覆盖率报告
```bash
# 使用提供的脚本
./scripts/run_coverage.sh

# 或手动运行
bazel coverage //test:binary_tree_test --combined_report=lcov
```

### 覆盖率报告类型
- **函数覆盖率**: 显示每个函数的调用情况
- **行覆盖率**: 显示每行代码的执行情况
- **分支覆盖率**: 显示条件分支的执行情况

### 报告文件位置
- HTML报告: `coverage_reports/coverage_report.html`
- XML报告: `coverage_reports/coverage_report.xml`
- 函数覆盖率: `coverage_reports/function_coverage.txt`
- 行覆盖率: `coverage_reports/line_coverage.txt`
- 分支覆盖率: `coverage_reports/branch_coverage.txt`
- 覆盖率摘要: `coverage_reports/coverage_summary.txt`

## 测试用例说明

测试用例覆盖以下功能：

### 基本操作测试
- 插入操作测试
- 搜索操作测试
- 删除操作测试
- 清空操作测试

### 遍历测试
- 中序遍历测试
- 前序遍历测试
- 后序遍历测试

### 树属性测试
- 大小测试
- 高度测试
- 深度测试
- 最小值/最大值测试

### 树验证测试
- 平衡性测试
- BST验证测试

### 边界条件测试
- 空树测试
- 单节点测试
- 重复值测试
- 大数值测试

## 开发说明

### 添加新功能
1. 在 `src/binary_tree.h` 中添加新方法
2. 在 `test/binary_tree_test.cc` 中添加对应测试
3. 运行测试确保功能正确
4. 生成覆盖率报告验证测试覆盖

### 代码风格
- 使用C++11及以上特性
- 遵循Google C++代码规范
- 所有公共方法都需要有对应的测试用例

## 故障排除

### 常见问题
1. **Bazel依赖下载失败**: 检查网络连接，可能需要配置代理
2. **覆盖率报告为空**: 确保使用 `--combined_report=lcov` 参数
3. **测试失败**: 检查编译器版本和依赖库版本

### 调试技巧
- 使用 `bazel test --test_output=all` 查看详细测试输出
- 使用 `bazel query --output=location //test:binary_tree_test` 查看测试位置
- 使用 `bazel info` 查看Bazel配置信息 