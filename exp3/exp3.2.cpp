//
// Created by 舒意恒 on 2018/7/5.
//

#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include "PTE.h"
#include <queue>

#define PTE_SIZE 4 // 主存中的页表项数
#define BLOCK_SIZE 10 // 主存块数
#define blockSize 128 // 每块长度
using namespace std;

bool block[BLOCK_SIZE + 5];

int main() {
    ifstream ifs;
    ifs.open("D:\\CLionProjects1\\os_experiment\\exp3\\operation.txt");
    if (!ifs) {
        cout << "打开文件失败" << endl;
        return 0;
    }
    vector<PTE> pageTable;
    queue<PTE *> queue;

    // 初始化页表
    PTE PTE0(0, 1, 5, 11); // 页号，标志，主存块号，磁盘位置
    block[5] = true;
    queue.push(&PTE0);
    PTE PTE1(1, 1, 8, 12);
    block[8] = true;
    queue.push(&PTE1);
    PTE PTE2(2, 1, 9, 13);
    block[9] = true;
    queue.push(&PTE2);
    PTE PTE3(3, 1, 1, 21);
    block[1] = true;
    queue.push(&PTE3);
    PTE PTE4(4, 0, 22); // 页号，标志，磁盘位置
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
                    if (operation == "存")
                        pte.modifyMark = 1;  // 置修改标志“1”
                    cout << "绝对地址: " << bitset<sizeof(int) * 3>(absoluteAddress) << endl;
                } else { // 不存在于主存，发生缺页中断
                    // 输出*页号
                    cout << "缺页异常: *" << pte.number << endl;
                    // 模拟FIFO页面调度
                    PTE *front = queue.front();
                    queue.pop();
                    if (front->modifyMark) { // 队首的修改标志为1
                        cout << "OUT " << front->number;
                        front->modifyMark = 0;
                        front->mark = 0;
                        block[front->memoryBlock] = false;
                    }
                    queue.push(&pte);
                    pte.mark = 1;
                    for (int i = 0; i < blockSize; i++) {
                        if (!block[i])
                            block[i] = true;
                        pte.memoryBlock = i;
                    }
                    cout << "IN " << pageNum;
                }
            }
        }
    }
    ifs.close();
    return 0;
}
