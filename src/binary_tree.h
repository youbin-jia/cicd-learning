#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <limits>

template<typename T>
struct TreeNode {
    T data;
    std::unique_ptr<TreeNode<T>> left;
    std::unique_ptr<TreeNode<T>> right;
    
    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTree {
private:
    std::unique_ptr<TreeNode<T>> root;
    size_t size_;
    
    // Helper functions
    void insertRecursive(std::unique_ptr<TreeNode<T>>& node, const T& value);
    bool searchRecursive(const std::unique_ptr<TreeNode<T>>& node, const T& value) const;
    void inorderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& result) const;
    void preorderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& result) const;
    void postorderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& result) const;
    int getHeightRecursive(const std::unique_ptr<TreeNode<T>>& node) const;
    int getDepthRecursive(const std::unique_ptr<TreeNode<T>>& node, const T& value, int depth) const;
    std::unique_ptr<TreeNode<T>> findMinRecursive(std::unique_ptr<TreeNode<T>>& node);
    std::unique_ptr<TreeNode<T>> removeRecursive(std::unique_ptr<TreeNode<T>>& node, const T& value);
    void clearRecursive(std::unique_ptr<TreeNode<T>>& node);
    bool isBalancedRecursive(const std::unique_ptr<TreeNode<T>>& node, int& height) const;
    bool isBSTRecursive(const std::unique_ptr<TreeNode<T>>& node, T min_val, T max_val) const;

public:
    BinaryTree() : root(nullptr), size_(0) {}
    ~BinaryTree() = default;
    
    // Basic operations
    void insert(const T& value);
    bool search(const T& value) const;
    bool remove(const T& value);
    void clear();
    
    // Traversal methods
    std::vector<T> inorder() const;
    std::vector<T> preorder() const;
    std::vector<T> postorder() const;
    
    // Tree properties
    size_t getSize() const { return size_; }
    bool isEmpty() const { return root == nullptr; }
    int getHeight() const;
    int getDepth(const T& value) const;
    T getMin() const;
    T getMax() const;
    
    // Tree validation
    bool isBalanced() const;
    bool isBST() const;
    
    // Utility methods
    bool contains(const T& value) const { return search(value); }
    void add(const T& value) { insert(value); }
};

// Implementation
template<typename T>
void BinaryTree<T>::insertRecursive(std::unique_ptr<TreeNode<T>>& node, const T& value) {
    if (!node) {
        node = std::make_unique<TreeNode<T>>(value);
        size_++;
        return;
    }
    
    if (value < node->data) {
        insertRecursive(node->left, value);
    } else if (value > node->data) {
        insertRecursive(node->right, value);
    }
    // If value == node->data, do nothing (duplicate)
}

template<typename T>
void BinaryTree<T>::insert(const T& value) {
    insertRecursive(root, value);
}

template<typename T>
bool BinaryTree<T>::searchRecursive(const std::unique_ptr<TreeNode<T>>& node, const T& value) const {
    if (!node) {
        return false;
    }
    
    if (value == node->data) {
        return true;
    } else if (value < node->data) {
        return searchRecursive(node->left, value);
    } else {
        return searchRecursive(node->right, value);
    }
}

template<typename T>
bool BinaryTree<T>::search(const T& value) const {
    return searchRecursive(root, value);
}

template<typename T>
void BinaryTree<T>::inorderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& result) const {
    if (node) {
        inorderTraversal(node->left, result);
        result.push_back(node->data);
        inorderTraversal(node->right, result);
    }
}

template<typename T>
std::vector<T> BinaryTree<T>::inorder() const {
    std::vector<T> result;
    inorderTraversal(root, result);
    return result;
}

template<typename T>
void BinaryTree<T>::preorderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& result) const {
    if (node) {
        result.push_back(node->data);
        preorderTraversal(node->left, result);
        preorderTraversal(node->right, result);
    }
}

template<typename T>
std::vector<T> BinaryTree<T>::preorder() const {
    std::vector<T> result;
    preorderTraversal(root, result);
    return result;
}

template<typename T>
void BinaryTree<T>::postorderTraversal(const std::unique_ptr<TreeNode<T>>& node, std::vector<T>& result) const {
    if (node) {
        postorderTraversal(node->left, result);
        postorderTraversal(node->right, result);
        result.push_back(node->data);
    }
}

template<typename T>
std::vector<T> BinaryTree<T>::postorder() const {
    std::vector<T> result;
    postorderTraversal(root, result);
    return result;
}

template<typename T>
int BinaryTree<T>::getHeightRecursive(const std::unique_ptr<TreeNode<T>>& node) const {
    if (!node) {
        return -1;
    }
    
    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);
    
    return std::max(leftHeight, rightHeight) + 1;
}

template<typename T>
int BinaryTree<T>::getHeight() const {
    return getHeightRecursive(root);
}

template<typename T>
int BinaryTree<T>::getDepthRecursive(const std::unique_ptr<TreeNode<T>>& node, const T& value, int depth) const {
    if (!node) {
        return -1;
    }
    
    if (value == node->data) {
        return depth;
    } else if (value < node->data) {
        return getDepthRecursive(node->left, value, depth + 1);
    } else {
        return getDepthRecursive(node->right, value, depth + 1);
    }
}

template<typename T>
int BinaryTree<T>::getDepth(const T& value) const {
    return getDepthRecursive(root, value, 0);
}

template<typename T>
T BinaryTree<T>::getMin() const {
    if (!root) {
        throw std::runtime_error("Tree is empty");
    }
    
    TreeNode<T>* current = root.get();
    while (current->left) {
        current = current->left.get();
    }
    return current->data;
}

template<typename T>
T BinaryTree<T>::getMax() const {
    if (!root) {
        throw std::runtime_error("Tree is empty");
    }
    
    TreeNode<T>* current = root.get();
    while (current->right) {
        current = current->right.get();
    }
    return current->data;
}

template<typename T>
std::unique_ptr<TreeNode<T>> BinaryTree<T>::findMinRecursive(std::unique_ptr<TreeNode<T>>& node) {
    if (!node->left) {
        return std::move(node);
    }
    return findMinRecursive(node->left);
}

template<typename T>
std::unique_ptr<TreeNode<T>> BinaryTree<T>::removeRecursive(std::unique_ptr<TreeNode<T>>& node, const T& value) {
    if (!node) {
        return nullptr;
    }
    
    if (value < node->data) {
        node->left = removeRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = removeRecursive(node->right, value);
    } else {
        // Node to delete found
        if (!node->left) {
            size_--;
            return std::move(node->right);
        } else if (!node->right) {
            size_--;
            return std::move(node->left);
        } else {
            // Node has two children
            auto successor = findMinRecursive(node->right);
            node->data = successor->data;
            node->right = removeRecursive(node->right, successor->data);
        }
    }
    return std::move(node);
}

template<typename T>
bool BinaryTree<T>::remove(const T& value) {
    size_t originalSize = size_;
    root = removeRecursive(root, value);
    return size_ < originalSize;
}

template<typename T>
void BinaryTree<T>::clearRecursive(std::unique_ptr<TreeNode<T>>& node) {
    if (node) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        node.reset();
    }
}

template<typename T>
void BinaryTree<T>::clear() {
    clearRecursive(root);
    size_ = 0;
}

template<typename T>
bool BinaryTree<T>::isBalancedRecursive(const std::unique_ptr<TreeNode<T>>& node, int& height) const {
    if (!node) {
        height = -1;
        return true;
    }
    
    int leftHeight, rightHeight;
    bool leftBalanced = isBalancedRecursive(node->left, leftHeight);
    bool rightBalanced = isBalancedRecursive(node->right, rightHeight);
    
    height = std::max(leftHeight, rightHeight) + 1;
    
    return leftBalanced && rightBalanced && 
           std::abs(leftHeight - rightHeight) <= 1;
}

template<typename T>
bool BinaryTree<T>::isBalanced() const {
    int height;
    return isBalancedRecursive(root, height);
}

template<typename T>
bool BinaryTree<T>::isBSTRecursive(const std::unique_ptr<TreeNode<T>>& node, T min_val, T max_val) const {
    if (!node) {
        return true;
    }
    
    if (node->data <= min_val || node->data >= max_val) {
        return false;
    }
    
    return isBSTRecursive(node->left, min_val, node->data) &&
           isBSTRecursive(node->right, node->data, max_val);
}

template<typename T>
bool BinaryTree<T>::isBST() const {
    if (!root) {
        return true;
    }
    
    T min_val = std::numeric_limits<T>::lowest();
    T max_val = std::numeric_limits<T>::max();
    
    return isBSTRecursive(root->left, min_val, root->data) &&
           isBSTRecursive(root->right, root->data, max_val);
}

#endif // BINARY_TREE_H 