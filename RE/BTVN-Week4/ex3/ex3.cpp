#include <windows.h>
#include <tlhelp32.h>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <filesystem>

using namespace std;
vector <pair<string, FILETIME>> results;
vector<string> giai = {"1st", "2nd", "3rd"};

// Hàm so sánh thời gian FILETIME
bool cmpTime(pair<string, FILETIME> a, pair<string, FILETIME> b) {
    return CompareFileTime(&a.second, &b.second) < 0;
}

// Hàm lấy thời gian kết thúc
FILETIME getTime() {
    FILETIME creationTime, exitTime, kernelTime, userTime;
    HANDLE threadHandle = GetCurrentThread();
    if (GetThreadTimes(threadHandle, &creationTime, &exitTime, &kernelTime, &userTime)) {
        return exitTime;
    }
    FILETIME zeroTime = {0, 0};
    return zeroTime;
}

// Thread 1
void thread1() {
    ifstream file("1.txt");
    int count = 0;
    string word;

    while (file >> word) {
        count++;
    }
    file.close();

    results.push_back(make_pair("Thread 1", getTime()));
}

// Thread 2
void thread2() {
    int count = 0;

    for (const auto& entry : filesystem::directory_iterator(".")) {
        if (filesystem::is_regular_file(entry.status())) {
            count++;
        }
    }

    results.push_back(make_pair("Thread 2", getTime()));
}

// Thread 3
void thread3() {
    int count = 0;
    DWORD PID = 0;
    PROCESSENTRY32 processEntry;
    
    // Lấy danh sách các process đang chạy
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    // Duyệt qua các process và tìm explorer.exe
    if (Process32First(hProcessSnap, &processEntry)) {
        do {
            // if (wcscmp(processEntry.szExeFile, L"explorer.exe") == 0) {
            if (strcmp(processEntry.szExeFile, "explorer.exe") == 0) {
                PID = processEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(hProcessSnap, &processEntry));
    }
    CloseHandle(hProcessSnap);

    if (PID == 0) {
        cout << "Process explorer.exe not found" << endl;
        return;
    }

    // Đếm số thread trong explorer.exe
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 threadEntry;

    if (Thread32First(hThreadSnap, &threadEntry)) {
        do {
            if (threadEntry.th32OwnerProcessID == PID) {
                count++;
            }
        } while (Thread32Next(hThreadSnap, &threadEntry));
    }

    CloseHandle(hThreadSnap);

    results.push_back(make_pair("Thread 3", getTime()));
}



int main() {
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);

    t1.join();
    t2.join();
    t3.join();

    sort(results.begin(), results.end(), cmpTime);

    for (int i = 0; i < 3; i++) {
        cout << results[i].first << ": " << giai[i] << endl;
    }

    string ketthuc = "\nPress any character + Enter to exit the program!\n";
    cout << ketthuc;
    cin >> ketthuc;
    return 0;
}
