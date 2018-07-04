//
// Created by 舒意恒 on 2018/7/4.
//

#ifndef OS_EXPERIMENT_TREE_H
#define OS_EXPERIMENT_TREE_H

template<class T>
class TreeNode {
    TreeNode *parent; // 指向父结点
    vector<TreeNode *> child;
    T val;
};


#endif //OS_EXPERIMENT_TREE_H
