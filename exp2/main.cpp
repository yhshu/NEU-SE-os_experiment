//
// Created by 舒意恒 on 2018/6/29.
//
#include <iostream>
#include "PList.h"

using namespace std;


int main() {
    int CPUTime = 0;
    PList pList;
    PCB p1("P1", 2, 1);
    PCB p2("P2", 3, 5);
    PCB p3("P3", 1, 3);
    PCB p4("P4", 2, 4);
    PCB p5("P5", 4, 2);
    pList.add(p1);
    pList.add(p2);
    pList.add(p3);
    pList.add(p4);
    pList.add(p5);

    cout << "Name NeedTime Priority" << endl;
    p1.startInfo();
    p2.startInfo();
    p3.startInfo();
    p4.startInfo();
    p5.startInfo();

    cout << "\nOutput of priority:" << endl;
    bool final = false; // 标识是否为最后一次循环
    while (!pList.empty() || final) {
        cout << "\nCPUTime:" << (CPUTime++) << endl;
        cout << "Name CPUTime NeedTime Priority State" << endl;
        p1.runInfo();
        p2.runInfo();
        p3.runInfo();
        p4.runInfo();
        p5.runInfo();
        if (!final) {
            pList.run();
            if (pList.empty()) // 即将进入最后一次循环
                final = true;
        } else // 最后一次循环结束
            break;
    }

    cout << "\nThe processes have been finished." << endl;
    cout << "Name RoundTime WaitingTime" << endl;
    p1.finalInfo();
    p2.finalInfo();
    p3.finalInfo();
    p4.finalInfo();
    p5.finalInfo();
    return 0;
}
