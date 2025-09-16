#include <Windows.h>
#include <iostream>
#include <vector>

using namespace std;

struct ThreadData {
    vector<int> numbers;
};

unsigned __stdcall WorkerThread(void* param) {
    ThreadData* data = (ThreadData*)param;

    cout << "Worker thread: processing numbers: ";
    for (int num : data->numbers) {
        cout << num << " ";
        Sleep(50);
    }
    cout << endl;

    return 0;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> numbers(n);
    cout << "Enter " << n << " numbers: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    ThreadData data;
    data.numbers = numbers;

    HANDLE worker = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)WorkerThread,
        &data,
        0,
        NULL
    );

    if (worker == NULL) {
        cerr << "Failed to create thread" << endl;
        return 1;
    }

    WaitForSingleObject(worker, INFINITE);
    CloseHandle(worker);

    cout << "Thread finished" << endl;
    return 0;
}