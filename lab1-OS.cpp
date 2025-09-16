#include <Windows.h>
#include <iostream>
#include <process.h>
#include <vector>
#include <algorithm>

using namespace std;

struct ThreadData {
    vector<int> numbers;
    vector<int> multiples;
};

unsigned __stdcall WorkerThread(void* param) {
    ThreadData* data = (ThreadData*)param;
    vector<int>& arr = data->numbers;

    for (int num : arr) {
        if (num % 5 == 0) {
            data->multiples.push_back(num);
        }
    }

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

    int suspend_time;
    cout << "Enter suspend time (ms): ";
    cin >> suspend_time;

    ThreadData data;
    data.numbers = numbers;

    HANDLE worker;
    unsigned thread_ID;

    worker = (HANDLE)_beginthreadex(
        NULL,
        0,
        &WorkerThread,
        &data,
        0,
        &thread_ID
    );

    if (worker == NULL) {
        cerr << "Failed to create thread" << endl;
        return 1;
    }

    SuspendThread(worker);
    cout << "Thread suspended. Sleeping for " << suspend_time << " ms..." << endl;
    Sleep(suspend_time);
    ResumeThread(worker);
    //WaitForSingleObject(worker, INFINITE);

    cout << "Elements divisible by 5: ";
    if (data.multiples.empty()) cout << "none found";
    else {
        for (int num : data.multiples)
            cout << num << " ";
    }
    cout << endl;

    CloseHandle(worker);
    return 0;
}