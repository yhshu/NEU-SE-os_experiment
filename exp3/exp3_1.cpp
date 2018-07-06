//
// Created by 舒意恒 on 2018/7/3.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <bitset>
#include "PTE.h"

#define BLOCK_SIZE 128

using namespace std;

string operation; // 操作
int pageNum = 0; // 页号
int unitNum = 0; // 单位号
int absoluteAddress = 0; // 绝对地址

int main() {
    ifstream ifs("D:\\CLionProjects1\\os_experiment\\exp3\\operation.txt");
    if (!ifs) {
        cout << "打开文件失败" << endl;
        return 0;
    }
    vector<PTE *> pageTable;
    // 初始化页表
    PTE *PTE0 = new PTE(0, 1, 5, 11);
    PTE *PTE1 = new PTE(1, 1, 8, 12);
    PTE *PTE2 = new PTE(2, 1, 9, 13);
    PTE *PTE3 = new PTE(3, 1, 1, 21);
    PTE *PTE4 = new PTE(4, 0, 22);
    PTE *PTE5 = new PTE(5, 0, 23);
    PTE *PTE6 = new PTE(6, 0, 121);
    pageTable.push_back(PTE0);
    pageTable.push_back(PTE1);
    pageTable.push_back(PTE2);
    pageTable.push_back(PTE3);
    pageTable.push_back(PTE4);
    pageTable.push_back(PTE5);
    pageTable.push_back(PTE6);

    while (ifs >> operation) {
        ifs >> pageNum >> unitNum;
        for (PTE *pte:pageTable) {
            if (pte->number == pageNum) {
                cout << "=====================" << endl;
                cout << "操作   页号   单元号" << endl;
                cout << operation << "      " << pageNum << "      " << unitNum << endl;
                if (pte->mark == 1) { // 存在于主存，形成绝对地址
                    absoluteAddress = pte->memoryBlock * BLOCK_SIZE + unitNum;
                    cout << "绝对地址: " << bitset<sizeof(int) * 3>(static_cast<unsigned long long int>(absoluteAddress))
                         << endl;
                } else { // 不存在于主存，发生缺页中断
                    // 输出*页号
                    cout << "缺页异常: *" << pte->number << endl;
                }
                break;
            }
        }
    }
    for (PTE *pte:pageTable) {
        delete pte;
    }
    ifs.close();
    return 0;
}
