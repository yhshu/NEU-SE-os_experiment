//
// Created by 舒意恒 on 2018/6/29.
//

#ifndef OS_EXPERIMENT_PLIST_H
#define OS_EXPERIMENT_PLIST_H

#include "PCB.h"

class PList {
public:
    PCB *head; // 指向队首

    PList();

    void add(PCB &);

    void run();

    bool empty();

    void roundTimeUpdate(); // 更新队列中所有进程的周转时间

    void runInfo(PCB &);
};

PList::PList() {
    head = nullptr;
}

void PList::add(PCB &p) { // 按优先级插入，并置队首标志
    if (empty()) { // 队列为空，直接插入
        this->head = &p;
        return;
    }
    if (p.priority > head->priority) { // 将p置为队首
        p.next = head;
        this->head = &p;
        return;
    }
    PCB *pre = head;
    PCB *cur = head->next;
    while (cur != nullptr) {
        if (pre->priority >= p.priority && p.priority > cur->priority) {
            pre->next = &p;
            p.next = cur;
            cur = &p;
            return;
        }
        pre = pre->next;
        cur = cur->next;
    }
    pre->next = &p;
}

void PList::run() { // 队列运行新程序
    if (empty())
        return;
    PCB *toRun = head; // 取队首运行
    this->head = head->next; // 队首变化
    toRun->run();
    if (toRun->needTime > 0)
        this->add(*toRun);
    else
        toRun->state = PCB_FINISH;
    roundTimeUpdate(); // 更新周转时间
}

bool PList::empty() { // 判断队列是否为空
    return head == nullptr;
}

void PList::roundTimeUpdate() {
    PCB *cur = this->head;
    while (cur != nullptr) {
        (cur->roundTime)++;
        cur = cur->next;
    }
}

void PList::runInfo(PCB &p) {
    cout << p.name << "         " << p.needTime << "        " << p.needTime << "        " << p.priority << " "
         << p.getState() << endl;
    if (p.state == PCB_WORKING)
        p.state = PCB_READY;
}

#endif //OS_EXPERIMENT_PLIST_H
