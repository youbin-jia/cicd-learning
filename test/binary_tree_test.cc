#include <gtest/gtest.h>
#include "../src/binary_tree.h"
#include <vector>
#include <algorithm>

class BinaryTreeTest : public ::testing::Test {
protected:
    BinaryTree<int> tree;
    
    void SetUp() override {
        tree.clear();
    }
};

// Test basic insertion and search
TEST_F(BinaryTreeTest, InsertAndSearch) {
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 0);
    
    tree.insert(5);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 1);
    EXPECT_TRUE(tree.search(5));
    EXPECT_FALSE(tree.search(3));
    
    tree.insert(3);
    tree.insert(7);
    EXPECT_EQ(tree.getSize(), 3);
    EXPECT_TRUE(tree.search(3));
    EXPECT_TRUE(tree.search(7));
    EXPECT_FALSE(tree.search(10));
}

// Test duplicate insertion
TEST_F(BinaryTreeTest, DuplicateInsertion) {
    tree.insert(5);
    tree.insert(5);  // Duplicate
    EXPECT_EQ(tree.getSize(), 1);  // Should not increase size
    EXPECT_TRUE(tree.search(5));
}

// Test traversal methods
TEST_F(BinaryTreeTest, InorderTraversal) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    std::vector<int> expected = {1, 3, 5, 7, 9};
    std::vector<int> result = tree.inorder();
    EXPECT_EQ(result, expected);
}

TEST_F(BinaryTreeTest, PreorderTraversal) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    std::vector<int> result = tree.preorder();
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0], 5);  // Root should be first
}

TEST_F(BinaryTreeTest, PostorderTraversal) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    std::vector<int> result = tree.postorder();
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[4], 5);  // Root should be last
}

// Test tree properties
TEST_F(BinaryTreeTest, TreeHeight) {
    EXPECT_EQ(tree.getHeight(), -1);  // Empty tree
    
    tree.insert(5);
    EXPECT_EQ(tree.getHeight(), 0);  // Single node
    
    tree.insert(3);
    tree.insert(7);
    EXPECT_EQ(tree.getHeight(), 1);  // Two levels
    
    tree.insert(1);
    tree.insert(9);
    EXPECT_EQ(tree.getHeight(), 2);  // Three levels
}

TEST_F(BinaryTreeTest, NodeDepth) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    EXPECT_EQ(tree.getDepth(5), 0);  // Root
    EXPECT_EQ(tree.getDepth(3), 1);  // Level 1
    EXPECT_EQ(tree.getDepth(7), 1);  // Level 1
    EXPECT_EQ(tree.getDepth(1), 2);  // Level 2
    EXPECT_EQ(tree.getDepth(9), 2);  // Level 2
    EXPECT_EQ(tree.getDepth(10), -1);  // Not found
}

TEST_F(BinaryTreeTest, MinMaxValues) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    EXPECT_EQ(tree.getMin(), 1);
    EXPECT_EQ(tree.getMax(), 9);
}

// Test edge cases
TEST_F(BinaryTreeTest, EmptyTreeOperations) {
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 0);
    EXPECT_EQ(tree.getHeight(), -1);
    EXPECT_FALSE(tree.search(5));
    EXPECT_EQ(tree.getDepth(5), -1);
    
    EXPECT_THROW(tree.getMin(), std::runtime_error);
    EXPECT_THROW(tree.getMax(), std::runtime_error);
}

TEST_F(BinaryTreeTest, SingleNodeTree) {
    tree.insert(5);
    
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 1);
    EXPECT_EQ(tree.getHeight(), 0);
    EXPECT_TRUE(tree.search(5));
    EXPECT_FALSE(tree.search(3));
    EXPECT_EQ(tree.getDepth(5), 0);
    EXPECT_EQ(tree.getMin(), 5);
    EXPECT_EQ(tree.getMax(), 5);
}

// Test utility methods
TEST_F(BinaryTreeTest, ContainsMethod) {
    tree.insert(5);
    tree.insert(3);
    
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_FALSE(tree.contains(7));
}

TEST_F(BinaryTreeTest, AddMethod) {
    tree.add(5);
    tree.add(3);
    
    EXPECT_EQ(tree.getSize(), 2);
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(3));
}

// Test remove functionality
TEST_F(BinaryTreeTest, RemoveOperation) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    
    EXPECT_TRUE(tree.remove(3));
    EXPECT_EQ(tree.getSize(), 2);
    EXPECT_FALSE(tree.search(3));
    
    EXPECT_FALSE(tree.remove(10));  // Non-existent value
    EXPECT_EQ(tree.getSize(), 2);
}

// Test clear functionality
TEST_F(BinaryTreeTest, ClearOperation) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    
    EXPECT_EQ(tree.getSize(), 3);
    tree.clear();
    
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.getSize(), 0);
    EXPECT_EQ(tree.getHeight(), -1);
    EXPECT_FALSE(tree.search(5));
}

// Test with different data types
TEST_F(BinaryTreeTest, StringTree) {
    BinaryTree<std::string> stringTree;
    
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");
    
    EXPECT_EQ(stringTree.getSize(), 3);
    EXPECT_TRUE(stringTree.search("apple"));
    EXPECT_TRUE(stringTree.search("banana"));
    EXPECT_FALSE(stringTree.search("orange"));
    
    std::vector<std::string> expected = {"apple", "banana", "cherry"};
    std::vector<std::string> result = stringTree.inorder();
    EXPECT_EQ(result, expected);
}

// Test complex tree structure
TEST_F(BinaryTreeTest, ComplexTreeStructure) {
    // Create a more complex tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(11);
    tree.insert(13);
    tree.insert(16);
    tree.insert(20);
    
    EXPECT_EQ(tree.getSize(), 15);
    EXPECT_EQ(tree.getHeight(), 3);
    
    // Test all values are present
    std::vector<int> values = {1, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 15, 16, 18, 20};
    for (int value : values) {
        EXPECT_TRUE(tree.search(value)) << "Value " << value << " should be found";
    }
    
    // Test non-existent values
    std::vector<int> nonValues = {2, 9, 14, 17, 19, 21};
    for (int value : nonValues) {
        EXPECT_FALSE(tree.search(value)) << "Value " << value << " should not be found";
    }
    
    // Test inorder traversal
    std::vector<int> result = tree.inorder();
    EXPECT_EQ(result, values);
}

// Test boundary conditions
TEST_F(BinaryTreeTest, BoundaryConditions) {
    // Test with large numbers
    tree.insert(1000000);
    tree.insert(-1000000);
    tree.insert(0);
    
    EXPECT_EQ(tree.getSize(), 3);
    EXPECT_EQ(tree.getMin(), -1000000);
    EXPECT_EQ(tree.getMax(), 1000000);
    
    // Test with repeated operations
    for (int i = 0; i < 10; i++) {
        tree.insert(5);
    }
    EXPECT_EQ(tree.getSize(), 3);  // Should not increase due to duplicates
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 