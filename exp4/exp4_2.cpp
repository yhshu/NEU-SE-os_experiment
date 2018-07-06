//
// Created by 舒意恒 on 2018/7/4.
//

#include <iostream>
#include "TreeNode.h"

using namespace std;

class File {
public:
    string filename;
    bool dir; // 目录或文件

    string to_string() {
        return filename;
    }

    File(string f, bool dir) : filename(f), dir(dir) {}

    ~File() {}
};

void initFileTree(TreeNode<File> &); // 初始化文件
void printPath(TreeNode<File> *); // 打印路径
void listFiles(TreeNode<File> *); // 列举文件

int main() {
    TreeNode<File> root(File("root", true));
    initFileTree(root);
    TreeNode<File> *curDir = &root; // 当前目录
    while (true) {
        int command = 0;
        bool quit = false;
        printPath(curDir); // 打印当前目录
        listFiles(curDir);
        cout << "=============" << endl;
        cout << "1.新建文件或目录" << endl;
        cout << "2.删除文件或目录" << endl;
        cout << "3.打开目录" << endl;
        cout << "4.返回上一级" << endl;
        cout << "5.退出" << endl;
        cout << "=============" << endl;
        cin >> command;
        switch (command) {
            case 1: {
                string createFile;
                int dir = 0;
                bool allow = true;
                cout << "请输入新文件名称与类型，1为目录，0为文件：" << endl;
                cin >> createFile >> dir;
                bool isDir = (dir == 1);
                TreeNode<File> *cur = curDir->firstChild;
                while (cur != nullptr) {
                    if (cur->val.filename == createFile) {
                        cout << "[错误]文件名重复" << endl;
                        allow = false;
                        break;
                    }
                    cur = cur->nextSibling;
                }
                if (allow) {
                    TreeNode<File> *newFile = new TreeNode<File>(File(createFile, isDir));
                    curDir->insert(newFile);
                }
                break;
            }
            case 2: {
                string deleteFile;
                bool success = false;
                cout << "请输入删除文件或目录名：" << endl;
                cin >> deleteFile;
                TreeNode<File> *cur = curDir->firstChild;
                while (cur != nullptr) {
                    if (cur->val.filename == deleteFile) {
                        cur->Delete();
                        success = true;
                        break;
                    }
                    cur = cur->nextSibling;
                }
                if (!success)
                    cout << "[信息]操作异常" << endl;
                break;
            }
            case 3: {
                string openDir;
                bool success = false;
                cout << "请输入打开目录名：" << endl;
                cin >> openDir;
                TreeNode<File> *cur = curDir->firstChild;
                while (cur != nullptr) {
                    if (cur->val.filename == openDir && cur->val.dir) {
                        curDir = cur;
                        success = true;
                        break;
                    }
                    cur = cur->nextSibling;
                }
                if (!success)
                    cout << "[信息]操作异常" << endl;
                break;
            }
            case 4: {
                if (curDir->parent != nullptr)
                    curDir = curDir->parent;
                break;
            }
            case 5: {
                quit = true;
                break;
            }
            default:
                break;
        }
        if (quit)
            break;
    }
    root.Delete();
    return 0;
}

void initFileTree(TreeNode<File> &root) {

}

void printPath(TreeNode<File> *curDir) {
    if (curDir->val.dir)
        cout << "当前路径：" << curDir->getPath() << endl;
}

void listFiles(TreeNode<File> *curDir) {
    cout << "文件列表：" << endl;
    bool empty = true;
    TreeNode<File> *cur = curDir->firstChild;
    while (cur != nullptr) {
        empty = false;
        cout << "文件名：" << cur->val.filename << " ，文件类型：" << (cur->val.dir ? "目录" : "文件") << endl;
        cur = cur->nextSibling;
    }
    if (empty)
        cout << "暂无文件" << endl;
}