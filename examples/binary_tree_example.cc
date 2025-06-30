#include "../src/binary_tree.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== 二叉树示例程序 ===" << std::endl;
    
    // 创建二叉树
    BinaryTree<int> tree;
    
    // 插入数据
    std::vector<int> data = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    
    std::cout << "插入数据: ";
    for (int value : data) {
        std::cout << value << " ";
        tree.insert(value);
    }
    std::cout << std::endl;
    
    // 显示树的基本信息
    std::cout << "树的大小: " << tree.getSize() << std::endl;
    std::cout << "树的高度: " << tree.getHeight() << std::endl;
    std::cout << "树是否为空: " << (tree.isEmpty() ? "是" : "否") << std::endl;
    
    // 遍历
    std::cout << "\n中序遍历: ";
    auto inorder = tree.inorder();
    for (int value : inorder) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "前序遍历: ";
    auto preorder = tree.preorder();
    for (int value : preorder) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "后序遍历: ";
    auto postorder = tree.postorder();
    for (int value : postorder) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    // 搜索测试
    std::cout << "\n搜索测试:" << std::endl;
    std::vector<int> search_values = {50, 25, 90, 35, 100};
    for (int value : search_values) {
        bool found = tree.search(value);
        std::cout << "搜索 " << value << ": " << (found ? "找到" : "未找到") << std::endl;
    }
    
    // 树属性
    std::cout << "\n树属性:" << std::endl;
    std::cout << "最小值: " << tree.getMin() << std::endl;
    std::cout << "最大值: " << tree.getMax() << std::endl;
    std::cout << "是否平衡: " << (tree.isBalanced() ? "是" : "否") << std::endl;
    std::cout << "是否二叉搜索树: " << (tree.isBST() ? "是" : "否") << std::endl;
    
    // 深度测试
    std::cout << "\n深度测试:" << std::endl;
    for (int value : {50, 30, 70, 20, 80}) {
        int depth = tree.getDepth(value);
        std::cout << "节点 " << value << " 的深度: " << depth << std::endl;
    }
    
    // 删除测试
    std::cout << "\n删除测试:" << std::endl;
    std::vector<int> delete_values = {20, 70, 50};
    for (int value : delete_values) {
        bool removed = tree.remove(value);
        std::cout << "删除 " << value << ": " << (removed ? "成功" : "失败") << std::endl;
        std::cout << "删除后树的大小: " << tree.getSize() << std::endl;
    }
    
    std::cout << "\n删除后的中序遍历: ";
    inorder = tree.inorder();
    for (int value : inorder) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== 示例程序结束 ===" << std::endl;
    return 0;
} 