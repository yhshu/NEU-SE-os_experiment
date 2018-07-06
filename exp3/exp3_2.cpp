//
// Created by 舒意恒 on 2018/7/5.
//

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <fstream>
#include "PTE.h"

#define BLOCK_SIZE 128 // 每块长度
using namespace std;

string operation; // 操作
int pageNum; // 页号
int unitNum; // 单位号
int absoluteAddress; // 绝对地址
vector<PTE *> pageTable;
queue<PTE *> que;

bool executeInstruction();

int main() {
    ifstream ifs("D:\\CLionProjects1\\os_experiment\\exp3\\operation.txt");
    if (!ifs) {
        cout << "打开文件失败" << endl;
        return 0;
    }
    // 初始化页表
    PTE PTE0(0, 1, 5, 11); // 页号，标志，主存块号，磁盘位置
    que.push(&PTE0);
    PTE PTE1(1, 1, 8, 12);
    que.push(&PTE1);
    PTE PTE2(2, 1, 9, 13);
    que.push(&PTE2);
    PTE PTE3(3, 1, 1, 21);
    que.push(&PTE3);
    PTE PTE4(4, 0, 22); // 页号，标志，磁盘位置
    PTE PTE5(5, 0, 23);
    PTE PTE6(6, 0, 121);
    pageTable.push_back(&PTE0);
    pageTable.push_back(&PTE1);
    pageTable.push_back(&PTE2);
    pageTable.push_back(&PTE3);
    pageTable.push_back(&PTE4);
    pageTable.push_back(&PTE5);
    pageTable.push_back(&PTE6);

    while (ifs >> operation) {
        ifs >> pageNum >> unitNum;
        if (!executeInstruction())
            executeInstruction();
    }
    ifs.close();
    return 0;
}

bool executeInstruction() {
    bool res = false;
    for (PTE *pte:pageTable) {
        if (pte->number == pageNum) {
            cout << "=====================" << endl;
            cout << "操作   页号   单元号" << endl;
            cout << operation << "      " << pageNum << "      " << unitNum << endl;
            if (pte->mark == 1) { // 存在于主存，形成绝对地址
                res = true;
                absoluteAddress = pte->memoryBlock * BLOCK_SIZE + unitNum;
                if (operation == "存")
                    pte->modifyMark = 1;  // 置修改标志“1”
                cout << "绝对地址: " << bitset<sizeof(int) * 3>(absoluteAddress) << endl;
            } else { // 不存在于主存，发生缺页中断
                res = false;
                // 输出*页号
                cout << "缺页异常: *" << pte->number << endl;
                // 模拟FIFO页面调度
                PTE *front = que.front();
                que.pop();
                if (front->modifyMark) { // 队首的修改标志为1
                    cout << "OUT " << front->number << endl;
                    front->modifyMark = 0;
                }
                front->mark = 0;
                que.push(pte);
                pte->memoryBlock = front->memoryBlock;
                pte->mark = 1;
                pte->modifyMark = 0;
                cout << "IN " << pageNum << endl;
                // 重新执行指令
            }
            break;
        }
    }
    return res;
}
