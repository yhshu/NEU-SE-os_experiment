//
// Created by 舒意恒 on 2018/7/3.
//

#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include "PTE.h"

using namespace std;

int main() {
    ifstream ifs;
    ifs.open("D:\\CLionProjects1\\os_experiment\\exp3\\operation.txt");
    if (!ifs) {
        cout << "打开文件失败" << endl;
        return 0;
    }
    const int blockSize = 128; // 每块长度
    vector<PTE> pageTable;
    // 初始化页表
    PTE PTE0(0, 1, 5, 11);
    PTE PTE1(1, 1, 8, 12);
    PTE PTE2(2, 1, 9, 13);
    PTE PTE3(3, 1, 1, 21);
    PTE PTE4(4, 0, 22);
    PTE PTE5(5, 0, 23);
    PTE PTE6(6, 0, 121);
    pageTable.push_back(PTE0);
    pageTable.push_back(PTE1);
    pageTable.push_back(PTE2);
    pageTable.push_back(PTE3);
    pageTable.push_back(PTE4);
    pageTable.push_back(PTE5);
    pageTable.push_back(PTE6);

    string operation; // 操作
    int pageNum; // 页号
    int unitNum; // 单位号
    int memoryBlock = 0; // 主存块号
    int absoluteAddress; // 绝对地址
    while (ifs >> operation) {
        ifs >> pageNum >> unitNum;
        for (PTE &pte:pageTable) {
            if (pte.number == pageNum) {
                cout << "=====================" << endl;
                cout << "操作   页号   单元号" << endl;
                cout << operation << "      " << pageNum << "      " << unitNum << endl;
                if (pte.mark == 1) { // 存在于主存，形成绝对地址
                    memoryBlock = pte.memoryBlock;
                    absoluteAddress = memoryBlock * blockSize + unitNum;
                    cout << "绝对地址: " << bitset<sizeof(int) * 3>(absoluteAddress) << endl;
                } else { // 不存在于主存，发生缺页中断
                    // 输出*页号
                    cout << "缺页异常: *" << pte.number << endl;
                }
            }
        }
    }
    ifs.close();
    return 0;
}
