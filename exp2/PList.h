//
// Created by 舒意恒 on 2018/6/29.
//

#ifndef OS_EXPERIMENT_PLIST_H
#define OS_EXPERIMENT_PLIST_H

#include "PCB.h"

class PList {
    PCB *head;

    void add(PCB &p) { // 按优先级插入，并置队首标志
    }

    void run() { // 队列运行新程序
        if (empty())
            return;
        PCB *toRun = head; // 取队首运行
        this->head = head->next; // 队首变化
        toRun->run();
        if (toRun->needTime > 0)
            add(toRun);
        else toRun->state = PCB_FINISH;
    }

    bool empty() { // 判断队列是否为空
        return head == nullptr;
    }
};


#endif //OS_EXPERIMENT_PLIST_H
