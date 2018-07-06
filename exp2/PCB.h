//
// Created by 舒意恒 on 2018/6/29.
//

#ifndef OS_EXPERIMENT_PCB_H
#define OS_EXPERIMENT_PCB_H

using namespace std;

#define PCB_READY   'R'  // 就绪状态，是初始状态
#define PCB_WORKING 'W'  // 运行状态
#define PCB_FINISH  'E'  // 完成状态

class PCB {
public:
    string name;   // 进程名
    PCB *next;    // 指针：指向下一个进程的 PCB 首地址，最后一个进程的指针为0
    int needTime;  // 要求运行时间
    int priority; // 优先数：优先数大的进程优先
    char state;    // 状态
    int roundTime; // 周转时间：从进程提交到进程完成的时间长度
    int waitingTime; // 等待时间：在就绪队列中等待所花费的时间之和
    bool started;   // 是否运行过
    int CPUTime;    // 从第一次开始运行到某一时刻的时间长度

    PCB(string, int, int);

    void run();       // 运行

    string getState();// 获取进程状态

    void startInfo(); // 初始状态标准输出

    void runInfo();   // 运行过程中标准输出

    void finalInfo(); // 运行结束后标准输出
};

PCB::PCB(string name, int time, int pri) : name(name), needTime(time), priority(pri),
                                           state(PCB_READY), next(nullptr), roundTime(0),
                                           waitingTime(0), started(false), CPUTime(0) {
}

void PCB::run() {
    this->next = nullptr; // 从就绪队列中移出
    this->priority--; // 优先级
    this->needTime--; // 剩余所需运行时间
    this->state = PCB_WORKING;
    this->started = true; // 被调度过
}

string PCB::getState() {
    if (this->state == PCB_READY)
        return "ready";
    else if (this->state == PCB_WORKING)
        return "working";
    else if (this->state == PCB_FINISH)
        return "finish";
}

void PCB::startInfo() {
    cout << name << "          " << needTime << "        " << priority << endl;
}

void PCB::runInfo() {
    cout << name << "         " << CPUTime << "        " << needTime
         << "        " << priority << " " << getState() << endl;
    if (state == PCB_WORKING)
        state = PCB_READY;
}

void PCB::finalInfo() {
    cout << name << "         " << roundTime << "             " << waitingTime << endl;
}

#endif //OS_EXPERIMENT_PCB_H
