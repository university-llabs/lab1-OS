#include <Windows.h>
#include <iostream>
#include <process.h> 

using namespace std;

unsigned __stdcall workerThread(void* param) {
    cout << "Worker thread is working!\n";
    return 0;
}

int main() {
    HANDLE hThread;
    unsigned threadID;

    hThread = (HANDLE)_beginthreadex(
        NULL,           // ������������ �� ���������
        0,              // ������ ����� �� ���������
        &workerThread,  // ������� ������
        NULL,           // ��������� ��� �������� � ����� (���� ���)
        0,              // ����� �������� (0 - ��������� �����)
        &threadID       // [out] ID ������
    );

    if (hThread == NULL) {
        cerr << "Failed to create thread.\n";
        return 1;
    }

    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);
    cout << "Main thread is exiting.\n";

    return 0;
}