//
// Created by 舒意恒 on 2018/6/29.
//
#include <windows.h>
#include <iostream>

using namespace std;

const unsigned short SIZE_OF_BUFFER = 5;  // 缓冲区长度
unsigned short ProductItem = 0;               // 被生产item
unsigned short ConsumeItem = 0;               // 将消费item
unsigned short in = 0;                      // 产品进缓冲区时的缓冲区下标
unsigned short out = 0;                     // 产品出缓冲区时的缓冲区下标
int buffer[SIZE_OF_BUFFER];                  // 以循环队列作缓冲区
bool toContinue = true;                     // 控制程序结束
// 互斥量
HANDLE mutex;                                // 用于线程间互斥
// 信号量
HANDLE full;                                 // 当缓冲区满时，生产者阻塞
HANDLE empty;                                // 当缓冲区空时，消费者阻塞
// 线程
DWORD WINAPI Producer(LPVOID);               // 生产者线程
DWORD WINAPI Consumer(LPVOID);               // 消费者线程
// 函数声明
void Produce();                              // 生产
void Append();                               // 添加item到缓冲区
void Consume();                              // 消费
void Take();                                 // 从缓冲区取出item
void printBuffer();                          // 改变缓冲区后打印

int main() {
    // 创建互斥量
    mutex = CreateMutex(NULL, FALSE, NULL);
    full = CreateSemaphore(NULL, SIZE_OF_BUFFER - 1, SIZE_OF_BUFFER - 1, NULL);
    empty = CreateSemaphore(NULL, 0, SIZE_OF_BUFFER - 1, NULL);
    const unsigned short PRODUCERS_COUNT = 3; // 生产者个数
    const unsigned short CONSUMERS_COUNT = 3; // 消费者个数

    const unsigned short THREADS_COUNT = PRODUCERS_COUNT + CONSUMERS_COUNT; // 总线程数
    HANDLE threadHandle[THREADS_COUNT]; // 各线程句柄
    DWORD producerID[PRODUCERS_COUNT];  // 生产者线程的标识符
    DWORD consumerID[CONSUMERS_COUNT];  // 消费者线程的标识符

    // 创建生产者线程
    for (int i = 0; i < PRODUCERS_COUNT; ++i) {
        threadHandle[i] = CreateThread(NULL, 0, Producer, NULL, 0, &producerID[i]);
        if (threadHandle[i] == NULL) return -1;
    }
    // 创建消费者线程
    for (int i = 0; i < CONSUMERS_COUNT; ++i) {
        threadHandle[PRODUCERS_COUNT + i] = CreateThread(NULL, 0, Consumer, NULL, 0, &consumerID[i]);
        if (threadHandle[i] == NULL) return -1;
    }

    while (toContinue) {
        if (getchar()) { // 按任意键结束程序
            toContinue = false;
        }
    }
    return 0;
}

// 生产item
void Produce() {
    cerr << "生产 #" << ++ProductItem << " ... ";
    cerr << "完成" << endl;
}

// 将生产的item添加到缓冲区
void Append() {
    cerr << "添加 #" << ProductItem << " 到缓冲区... ";
    buffer[in] = ProductItem;
    in = static_cast<unsigned short>((in + 1) % SIZE_OF_BUFFER);
    cerr << "完成" << endl;
    // 输出缓冲区当前的状态
    printBuffer();
}

// 从缓冲区中取出item
void Take() {
    ConsumeItem = static_cast<unsigned short>(buffer[out]);
    cerr << "从缓冲区取出 #" << ConsumeItem << " ... ";
    buffer[out] = 0; // 置为0，表示空
    out = static_cast<unsigned short>((out + 1) % SIZE_OF_BUFFER);
    cerr << "完成" << endl;
    printBuffer();
}

void printBuffer() {
    for (int i = 0; i < SIZE_OF_BUFFER; ++i) {
        int cur = buffer[i];
        if (cur)
            cout << "[" << i << "]: #" << cur;
        else cout << "[" << i << "]: 空";
        if (i == in) cout << " <-- 生产";
        if (i == out) cout << " <-- 消费";
        cout << endl;
    }
    cout << endl;
}

// 消费item
void Consume() {
    cerr << "消费 #" << ConsumeItem << " ... ";
    cerr << "完成" << endl;
}

// 生产者线程
DWORD WINAPI Producer(LPVOID lpPara) {
    while (toContinue) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        Produce();
        Append();
        Sleep(500);
        ReleaseMutex(mutex);
        ReleaseSemaphore(empty, 1, NULL);
    }
    return 0;
}

// 消费者线程
DWORD WINAPI Consumer(LPVOID lpPara) {
    while (toContinue) {
        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        Take();
        Consume();
        Sleep(500);
        ReleaseMutex(mutex);
        ReleaseSemaphore(full, 1, NULL);
    }
    return 0;
}
