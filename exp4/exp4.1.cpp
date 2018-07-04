//
// Created by ����� on 2018/7/4.
//

#include <iostream>
#include <vector>
#include "MFDE.h"
#include "UFDE.h"
#include "AFDE.h"

#define USER_MAX 10 // ����û�����
#define SAVE_MAX 10 // ÿ���û����ɱ�����ļ�
#define OPEN_MAX 5  // ÿ���û����ɴ򿪵��ļ�
using namespace std;

void init(vector<MFDE> &);       // ��ʼ��
void CreateFile(); // �����ļ�
void DeleteFile(); // ɾ���ļ�
void OpenFile();   // ���ļ�
void CloseFile();  // �ر��ļ�
void ReadFile();   // ��ȡ�ļ�
void WriteFile();  // д���ļ�
void printMFD();

void printAFD();

vector<UFDE>::iterator getUFDE(string);

vector<AFDE>::iterator getAFDE(string);

vector<MFDE> MFD;
vector<AFDE> AFD;
MFDE *userMFDE;

int main() {
    init(MFD);  // ��ʼ��
    string user;
    while (true) {
        cout << "�������û�����" << endl;
        cin >> user;
        // ��MFD�в��Ҹ��û�
        bool find = false;
        for (MFDE &mfde:MFD) {
            if (mfde.username == user) {
                find = true;
                userMFDE = &mfde;
            }
        }
        if (find) break;
        else {
            cout << "�޴��û��ļ������������룺" << endl;
        }
    }
    while (true) {
        int command;
        bool quit = false;
        printMFD(); // ��ʾ���ļ���AFD
        printAFD();
        cout << "=============" << endl;
        cout << "1.�½��ļ�" << endl;
        cout << "2.ɾ���ļ�" << endl;
        cout << "3.���ļ�" << endl;
        cout << "4.�ر��ļ�" << endl;
        cout << "5.��ȡ�ļ�" << endl;
        cout << "6.д���ļ�" << endl;
        cout << "7.�˳�" << endl;
        cout << "=============" << endl;
        cin >> command;
        switch (command) {
            case 1:
                CreateFile();
                break;
            case 2:
                DeleteFile();
                break;
            case 3:
                OpenFile();
                break;
            case 4:
                CloseFile();
                break;
            case 5:
                ReadFile();
                break;
            case 6:
                WriteFile();
                break;
            case 7:
                quit = true;
                break;
            default:
                break;
        }
        if (quit)
            break;
    }
    // ���浱ǰ�ļ�Ŀ¼
    // ��ӡ��ǰ�ļ�Ŀ¼
    return 0;
}

void CreateFile() {
    string createFile;
    int protect;
    cout << "���������ļ�����Ȩ�ޣ�" << endl;
    cin >> createFile >> protect;
    if (getUFDE(createFile) != userMFDE->UFD.end()) {
        cout << "[����]���ļ��Ѵ���" << endl;
        return;
    }
    if (userMFDE->UFD.size() < SAVE_MAX) {
        userMFDE->UFD.push_back(UFDE(createFile, protect));
    } else {
        cout << "[����]�ļ����������ﵽ����" << endl;
        return;
    }
}

void DeleteFile() {
    string deleteFile;
    cout << "������ɾ���ļ�����" << endl;
    cin >> deleteFile;
    auto deleteUFDE = getUFDE(deleteFile);
    if (deleteUFDE == userMFDE->UFD.end()) {
        cout << "[����]���ļ�������" << endl;
        return;
    }
    userMFDE->UFD.erase(deleteUFDE);
}

void OpenFile() {
    string openFile;
    cout << "��������ļ�����" << endl;
    cin >> openFile;
    auto openUFDE = getUFDE(openFile);
    if (openUFDE == userMFDE->UFD.end()) {
        cout << "[����]���ļ�������" << endl;
        return;
    }
    AFD.push_back(AFDE(openUFDE->filename, openUFDE->protect));
}

void CloseFile() {
    string closeFile;
    cout << "������ر��ļ�����" << endl;
    cin >> closeFile;
    auto closeAFDE = getAFDE(closeFile);
    if (closeAFDE == AFD.end()) {
        cout << "[��Ϣ]���ļ�δ��" << endl;
        return;
    }
    AFD.erase(closeAFDE);
}

void ReadFile() {
    string readFile;
    int len = 0;
    cout << "�������ȡ�ļ����Ͷ�ȡ���ȣ�" << endl;
    cin >> readFile >> len;
    auto readAFDE = getAFDE(readFile);
    if (readAFDE == AFD.end()) {
        cout << "[����]���ļ������ڻ�δ��" << endl;
        return;
    }
    if (!readAFDE->protect) {
        cout << "[����]�޶�ȡȨ��" << endl;
        return;
    }
    auto readUFDE = getUFDE(readFile);
    readAFDE->read = min(readUFDE->len, len); // ģ���ȡ
    cout << "�Ѷ�ȡ " << readFile << " ������ " << readAFDE->read << endl;
}

void WriteFile() {
    string writeFile;
    int len = 0;
    cout << "������д���ļ�����д�볤�ȣ�" << endl;
    cin >> writeFile >> len;
    auto writeAFDE = getAFDE(writeFile);
    if (writeAFDE == AFD.end()) {
        cout << "[����]���ļ������ڻ�δ��" << endl;
        return;
    }
    if (!writeAFDE->protect) {
        cout << "[����]��д��Ȩ��" << endl;
        return;
    }
    auto writeUFDE = getUFDE(writeFile);
    writeUFDE->len += len;
    writeAFDE->write = writeUFDE->len; // ģ��д��
    cout << "��д�� " << writeFile << " ���ļ����� " << writeAFDE->write;
}

vector<UFDE>::iterator getUFDE(string filename) {
    for (auto i = userMFDE->UFD.begin(); i != userMFDE->UFD.end(); i++) {
        if ((*i).filename == filename)
            return i;
    }
    return userMFDE->UFD.end();
}

vector<AFDE>::iterator getAFDE(string filename) {
    for (auto i = AFD.begin(); i != AFD.end(); i++) {
        if ((*i).filename == filename)
            return i;
    }
    return AFD.end();
}

void init(vector<MFDE> &MFD) {
    MFD.push_back(MFDE("user1"));
    MFD.push_back(MFDE("user2"));
    MFD.push_back(MFDE("user3"));
    MFD.push_back(MFDE("user4"));
    MFD.push_back(MFDE("user5"));
    MFD.push_back(MFDE("user6"));
    MFD.push_back(MFDE("user7"));
    MFD.push_back(MFDE("user8"));
    MFD.push_back(MFDE("user9"));
    MFD.push_back(MFDE("user10"));
}

void printMFD() {
    cout << "�û��ļ���" << endl;
    if (!userMFDE->UFD.size()) {
        cout << "��" << endl;
        return;
    }
    for (UFDE &ufde:userMFDE->UFD) {
        cout << "�ļ�����" << ufde.filename << "�� ";
        cout << "�����룺" << ufde.protect << "�� ";
        cout << "�ļ����ȣ�" << ufde.len << endl;
    }
    cout << endl;
}

void printAFD() {
    cout << "���ļ���" << endl;
    if (!AFD.size()) {
        cout << "��" << endl;
        return;
    }
    for (AFDE &afde:AFD) {
        cout << "�ļ�����" << afde.filename << "�� ";
        cout << "�����룺" << afde.protect << "�� ";
        cout << "��ָ�룺" << afde.read << "�� ";
        cout << "дָ�룺" << afde.write << "�� ";
    }
    cout << endl;
}
