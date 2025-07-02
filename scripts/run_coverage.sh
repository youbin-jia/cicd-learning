#!/bin/bash

# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== 二叉树工程覆盖率测试 ===${NC}"

# 清理之前的构建
echo -e "${YELLOW}清理之前的构建...${NC}"
bazel clean --expunge

# 运行测试并生成覆盖率数据
echo -e "${YELLOW}运行测试并生成覆盖率数据...${NC}"
bazel clean --expunge
bazel test //test:binary_tree_test \
  --noenable_bzlmod --enable_workspace \
  --test_env=LLVM_PROFILE_FILE=$(pwd)/test.profraw \
  --cache_test_results=no --test_output=all \
  --spawn_strategy=local

llvm-profdata merge -sparse test.profraw -o test.profdata
llvm-cov show ../bazel-bin/test/binary_tree_test --instr-profile=test.profdata -format=html -output-dir=coverage_html

echo -e "${GREEN}覆盖率测试完成，结果已保存到 coverage_html/index.html 目录下${NC}"