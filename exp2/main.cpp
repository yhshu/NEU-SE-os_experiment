//
// Created by 舒意恒 on 2018/6/29.
//
#include <iostream>
#include "PCB.h"

using namespace std;

int main() {
    int CPUTime = 0;
    PList pList;
    pList.add(p1("P1", 2, 1));
    pList.add(p2("P2", 3, 5));
    pList.add(p3("P3", 1, 3));
    pList.add(p4("P4", 2, 4));
    pList.add(p5("P5", 4, 2));
    cout << "Name NeedTime Priority" << endl;

    cout << "Output of priority:" << endl;
    while (!pList.empty()) {
        cout << "CPUTime:" << (CPUTime++) << endl;
        cout << "Name CPUTime NeedTime Priority State" << endl;

    }
    return 0;
}
