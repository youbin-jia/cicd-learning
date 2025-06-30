#!/bin/bash
 
# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== 二叉树工程覆盖率测试 (简化版) ===${NC}"

# 清理之前的构建
echo -e "${YELLOW}清理之前的构建...${NC}"
bazel clean --expunge

# 运行测试并生成覆盖率数据
echo -e "${YELLOW}运行测试并生成覆盖率数据...${NC}"
bazel coverage //test:binary_tree_test --combined_report=lcov --test_output=all

# 检查测试是否成功
if [ $? -ne 0 ]; then
    echo -e "${RED}测试失败！${NC}"
    exit 1
fi

echo -e "${GREEN}测试成功完成！${NC}"

# 生成覆盖率报告
echo -e "${YELLOW}生成覆盖率报告...${NC}"

# 创建覆盖率报告目录
mkdir -p coverage_reports

# 查找覆盖率数据文件
echo -e "${YELLOW}查找覆盖率数据文件...${NC}"
find bazel-out -name "*.gcno" -o -name "*.gcda" | head -10

# 使用gcov生成详细报告
echo -e "${YELLOW}生成函数覆盖率报告...${NC}"
find bazel-out -name "*.gcno" -exec gcov -f {} \; > coverage_reports/function_coverage.txt 2>/dev/null

echo -e "${YELLOW}生成行覆盖率报告...${NC}"
find bazel-out -name "*.gcno" -exec gcov -l {} \; > coverage_reports/line_coverage.txt 2>/dev/null

echo -e "${YELLOW}生成分支覆盖率报告...${NC}"
find bazel-out -name "*.gcno" -exec gcov -b {} \; > coverage_reports/branch_coverage.txt 2>/dev/null

# 生成综合覆盖率报告
echo -e "${YELLOW}生成综合覆盖率报告...${NC}"
find bazel-out -name "*.gcno" -exec gcov -f -l -b {} \; > coverage_reports/comprehensive_coverage.txt 2>/dev/null

# 显示覆盖率摘要
echo -e "${GREEN}=== 覆盖率报告摘要 ===${NC}"
if [ -f coverage_reports/comprehensive_coverage.txt ]; then
    echo "覆盖率数据已生成，请查看以下文件："
    ls -la coverage_reports/
else
    echo "覆盖率数据生成失败，请检查编译器配置"
fi

echo -e "${GREEN}=== 详细报告位置 ===${NC}"
echo -e "函数覆盖率: ${YELLOW}coverage_reports/function_coverage.txt${NC}"
echo -e "行覆盖率: ${YELLOW}coverage_reports/line_coverage.txt${NC}"
echo -e "分支覆盖率: ${YELLOW}coverage_reports/branch_coverage.txt${NC}"
echo -e "综合覆盖率: ${YELLOW}coverage_reports/comprehensive_coverage.txt${NC}"

echo -e "${GREEN}覆盖率测试完成！${NC}" 