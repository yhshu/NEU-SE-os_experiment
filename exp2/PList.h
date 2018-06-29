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

    PCB *run();

    bool empty();

    void timeUpdate(); // 更新队列中进程的周转时间、CPU时间
};

PList::PList() {
    head = nullptr;
}

void PList::add(PCB &p) { // 按优先级插入，并置队首标志
    p.next = nullptr;
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

PCB *PList::run() { // 队列取队首运行
    if (empty())
        return nullptr;
    PCB *toRun = head; // 取队首
    this->head = head->next; // 队首变化
    toRun->run();
    if (toRun->needTime > 0)
        this->add(*toRun);
    else {
        toRun->CPUTime++;
        toRun->roundTime++;
        toRun->state = PCB_FINISH;
    }
    timeUpdate(); // 更新周转时间
    return toRun;
}

bool PList::empty() { // 判断队列是否为空
    return head == nullptr;
}

void PList::timeUpdate() { // 队列中进程时间更新
    PCB *cur = this->head;
    while (cur != nullptr) {
        cur->roundTime++;
        if (cur->started)
            cur->CPUTime++;
        if (cur->state == PCB_READY)
            cur->waitingTime++;
        cur = cur->next;
    }
}


#endif //OS_EXPERIMENT_PLIST_H
