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
    cout << "P1          " << p1.needTime << "        " << p1.priority << endl;
    cout << "P2          " << p2.needTime << "        " << p2.priority << endl;
    cout << "P3          " << p3.needTime << "        " << p3.priority << endl;
    cout << "P4          " << p4.needTime << "        " << p4.priority << endl;
    cout << "P5          " << p5.needTime << "        " << p5.priority << endl;

    cout << "\nOutput of priority:" << endl;
    while (!pList.empty()) {
        cout << "CPUTime:" << (CPUTime++) << endl;
        cout << "Name CPUTime NeedTime Priority State" << endl;
        pList.runInfo(p1);
        pList.runInfo(p2);
        pList.runInfo(p3);
        pList.runInfo(p4);
        pList.runInfo(p5);
        pList.run();
    }

    cout << "The processes have been finished." << endl;
    cout << "Name RoundTime WaitingTime" << endl;
    return 0;
}
