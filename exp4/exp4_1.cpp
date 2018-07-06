//
// Created by 舒意恒 on 2018/7/4.
//

#include <iostream>
#include <vector>
#include "MFDE.h"
#include "UFDE.h"
#include "AFDE.h"

#define USER_MAX 10 // 最大用户数量
#define SAVE_MAX 10 // 每个用户最多可保存的文件
#define OPEN_MAX 5  // 每个用户最多可打开的文件
using namespace std;

void init(vector<MFDE> &);       // 初始化
void CreateFile(); // 创建文件
void DeleteFile(); // 删除文件
void OpenFile();   // 打开文件
void CloseFile();  // 关闭文件
void ReadFile();   // 读取文件
void WriteFile();  // 写入文件
void printMFD();

void printAFD();

vector<UFDE>::iterator getUFDE(string);

vector<AFDE>::iterator getAFDE(string);

vector<MFDE> MFD;
vector<AFDE> AFD;
MFDE *userMFDE;

int main() {
    init(MFD);  // 初始化
    string user;
    while (true) {
        cout << "请输入用户名：" << endl;
        cin >> user;
        // 在MFD中查找该用户
        bool find = false;
        for (MFDE &mfde:MFD) {
            if (mfde.username == user) {
                find = true;
                userMFDE = &mfde;
            }
        }
        if (find) break;
        else {
            cout << "无此用户文件，请重新输入：" << endl;
        }
    }
    while (true) {
        int command;
        bool quit = false;
        printMFD(); // 显示打开文件表AFD
        printAFD();
        cout << "=============" << endl;
        cout << "1.新建文件" << endl;
        cout << "2.删除文件" << endl;
        cout << "3.打开文件" << endl;
        cout << "4.关闭文件" << endl;
        cout << "5.读取文件" << endl;
        cout << "6.写入文件" << endl;
        cout << "7.退出" << endl;
        cout << "=============" << endl;
        cin >> command;
        switch (command) {
            case 1:
                CreateFile();
                break;
            case 2:
                DeleteFile();
                break;
            case 3:
                OpenFile();
                break;
            case 4:
                CloseFile();
                break;
            case 5:
                ReadFile();
                break;
            case 6:
                WriteFile();
                break;
            case 7: {
                quit = true;
                break;
            }
            default:
                break;
        }
        if (quit)
            break;
    }
    // 保存当前文件目录
    // 打印当前文件目录
    return 0;
}

void CreateFile() {
    string createFile;
    int protect;
    cout << "请输入新文件名与权限：" << endl;
    cin >> createFile >> protect;
    if (getUFDE(createFile) != userMFDE->UFD.end()) {
        cout << "[错误]该文件已存在" << endl;
        return;
    }
    if (userMFDE->UFD.size() < SAVE_MAX) {
        userMFDE->UFD.push_back(UFDE(createFile, protect));
    } else {
        cout << "[错误]文件保存数量达到上限" << endl;
        return;
    }
}

void DeleteFile() {
    string deleteFile;
    cout << "请输入删除文件名：" << endl;
    cin >> deleteFile;
    auto deleteUFDE = getUFDE(deleteFile);
    if (deleteUFDE == userMFDE->UFD.end()) {
        cout << "[错误]该文件不存在" << endl;
        return;
    }
    userMFDE->UFD.erase(deleteUFDE);
}

void OpenFile() {
    string openFile;
    cout << "请输入打开文件名：" << endl;
    cin >> openFile;
    auto openUFDE = getUFDE(openFile);
    if (openUFDE == userMFDE->UFD.end()) {
        cout << "[错误]该文件不存在" << endl;
        return;
    }
    AFD.push_back(AFDE(openUFDE->filename, openUFDE->protect));
}

void CloseFile() {
    string closeFile;
    cout << "请输入关闭文件名：" << endl;
    cin >> closeFile;
    auto closeAFDE = getAFDE(closeFile);
    if (closeAFDE == AFD.end()) {
        cout << "[信息]该文件未打开" << endl;
        return;
    }
    AFD.erase(closeAFDE);
}

void ReadFile() {
    string readFile;
    int len = 0;
    cout << "请输入读取文件名和读取长度：" << endl;
    cin >> readFile >> len;
    auto readAFDE = getAFDE(readFile);
    if (readAFDE == AFD.end()) {
        cout << "[错误]该文件不存在或未打开" << endl;
        return;
    }
    if (!readAFDE->protect) {
        cout << "[错误]无读取权限" << endl;
        return;
    }
    auto readUFDE = getUFDE(readFile);
    readAFDE->read = min(readUFDE->len, len); // 模拟读取
    cout << "已读取 " << readFile << " ，长度 " << readAFDE->read << endl;
}

void WriteFile() {
    string writeFile;
    int len = 0;
    cout << "请输入写入文件名和写入长度：" << endl;
    cin >> writeFile >> len;
    auto writeAFDE = getAFDE(writeFile);
    if (writeAFDE == AFD.end()) {
        cout << "[错误]该文件不存在或未打开" << endl;
        return;
    }
    if (!writeAFDE->protect) {
        cout << "[错误]无写入权限" << endl;
        return;
    }
    auto writeUFDE = getUFDE(writeFile);
    writeUFDE->len += len;
    writeAFDE->write = writeUFDE->len; // 模拟写入
    cout << "已写入 " << writeFile << " ，文件长度 " << writeAFDE->write;
}

vector<UFDE>::iterator getUFDE(string filename) {
    for (auto i = userMFDE->UFD.begin(); i != userMFDE->UFD.end(); i++) {
        if ((*i).filename == filename)
            return i;
    }
    return userMFDE->UFD.end();
}

vector<AFDE>::iterator getAFDE(string filename) {
    for (auto i = AFD.begin(); i != AFD.end(); i++) {
        if ((*i).filename == filename)
            return i;
    }
    return AFD.end();
}

void init(vector<MFDE> &MFD) {
    MFD.push_back(MFDE("user1"));
    MFD.push_back(MFDE("user2"));
    MFD.push_back(MFDE("user3"));
    MFD.push_back(MFDE("user4"));
    MFD.push_back(MFDE("user5"));
    MFD.push_back(MFDE("user6"));
    MFD.push_back(MFDE("user7"));
    MFD.push_back(MFDE("user8"));
    MFD.push_back(MFDE("user9"));
    MFD.push_back(MFDE("user10"));
}

void printMFD() {
    cout << "用户文件表：" << endl;
    if (!userMFDE->UFD.size()) {
        cout << "空" << endl;
        return;
    }
    for (UFDE &ufde:userMFDE->UFD) {
        cout << "文件名：" << ufde.filename << "； ";
        cout << "保护码：" << ufde.protect << "； ";
        cout << "文件长度：" << ufde.len << endl;
    }
    cout << endl;
}

void printAFD() {
    cout << "打开文件表：" << endl;
    if (!AFD.size()) {
        cout << "空" << endl;
        return;
    }
    for (AFDE &afde:AFD) {
        cout << "文件名：" << afde.filename << "； ";
        cout << "保护码：" << afde.protect << "； ";
        cout << "读指针：" << afde.read << "； ";
        cout << "写指针：" << afde.write << "； ";
    }
    cout << endl;
}
