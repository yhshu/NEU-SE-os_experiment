//
// Created by 舒意恒 on 2018/7/4.
//

#ifndef OS_EXPERIMENT_TREE_H
#define OS_EXPERIMENT_TREE_H

#include <string>
#include <stack>
#include <cassert>

using namespace std;

template<class T>
class TreeNode {
public:
    TreeNode *firstChild;
    TreeNode *nextSibling;
    TreeNode *parent;
    T val;

    TreeNode(T val) :
            firstChild(nullptr), nextSibling(nullptr), parent(nullptr), val(val) {}

    void insert(TreeNode *child) { // 插入为子结点
        TreeNode *cur = this->firstChild;
        if (cur == nullptr) // 如果当前结点没有子结点
            this->firstChild = child;
        else {              // 如果当前结点含有子结点
            while (cur->nextSibling != nullptr) {
                cur = cur->nextSibling;
            }
            cur->nextSibling = child; // 新增为叶子结点
        }
        child->parent = this;
    }

    string getPath() {
        string path;
        stack<TreeNode *> stack;
        TreeNode *cur = this;
        stack.push(cur);
        while (cur->parent != nullptr) {
            stack.push(cur->parent);
            cur = cur->parent;
        }
        while (stack.size()) {
            TreeNode *top = stack.top();
            path += top->val.to_string() + "\\";
            stack.pop();
        }
        return path;
    }

    void Delete() {
        if (this->firstChild != nullptr) // 递归删除
            this->firstChild->Delete();
        TreeNode *cur = this->parent;
        if (cur != nullptr)
            cur = cur->firstChild;
        TreeNode *pre = cur;
        if (pre == this)
            this->parent->firstChild = this->nextSibling;
        else {
            cur = cur->nextSibling;
            assert(cur != nullptr);
            while (cur->nextSibling != nullptr) {
                if (cur == this) {
                    pre->nextSibling = cur->nextSibling;
                    break;
                }
                pre = pre->nextSibling;
                cur = cur->nextSibling;
            }
        }
        delete this;
    }
};

#endif //OS_EXPERIMENT_TREE_H
