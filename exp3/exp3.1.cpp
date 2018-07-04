//
// Created by ����� on 2018/7/3.
//

#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include "PTE.h"

using namespace std;

int main() {
    ifstream ifs;
    ifs.open("D:\\CLionProjects1\\os_experiment\\exp3\\operation.txt");
    if (!ifs) {
        cout << "���ļ�ʧ��" << endl;
        return 0;
    }
    const int blockSize = 128; // ÿ�鳤��
    vector<PTE> pageTable;
    // ��ʼ��ҳ��
    PTE PTE0(0, 1, 5, 11);
    PTE PTE1(1, 1, 8, 12);
    PTE PTE2(2, 1, 9, 13);
    PTE PTE3(3, 1, 1, 21);
    PTE PTE4(4, 0, 22);
    PTE PTE5(5, 0, 23);
    PTE PTE6(6, 0, 121);
    pageTable.push_back(PTE0);
    pageTable.push_back(PTE1);
    pageTable.push_back(PTE2);
    pageTable.push_back(PTE3);
    pageTable.push_back(PTE4);
    pageTable.push_back(PTE5);
    pageTable.push_back(PTE6);

    string operation; // ����
    int pageNum; // ҳ��
    int unitNum; // ��λ��
    int memoryBlock = 0; // ������
    int absoluteAddress; // ���Ե�ַ
    while (ifs >> operation) {
        ifs >> pageNum >> unitNum;
        for (PTE &pte:pageTable) {
            if (pte.number == pageNum) {
                cout << "=====================" << endl;
                cout << "����   ҳ��   ��Ԫ��" << endl;
                cout << operation << "      " << pageNum << "      " << unitNum << endl;
                if (pte.mark == 1) { // ���������棬�γɾ��Ե�ַ
                    memoryBlock = pte.memoryBlock;
                    absoluteAddress = memoryBlock * blockSize + unitNum;
                    cout << "���Ե�ַ: " << bitset<sizeof(int) * 3>(absoluteAddress) << endl;
                } else { // �����������棬����ȱҳ�ж�
                    // ���*ҳ��
                    cout << "ȱҳ�쳣: *" << pte.number << endl;
                }
            }
        }
    }
    ifs.close();
    return 0;
}
