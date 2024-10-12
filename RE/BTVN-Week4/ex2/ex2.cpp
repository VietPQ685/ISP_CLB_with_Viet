#include <windows.h>
#include <tlhelp32.h>
#include <bits/stdc++.h>
#include <string>

using namespace std;

DWORD findName(string processName) {
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::wcerr << L"CreateToolhelp32Snapshot failed!" << std::endl;
        return 0;
    }

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (processName == processEntry.szExeFile) {
                CloseHandle(snapshot);
                return processEntry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);
    return 0; // Không tìm thấy
}

bool killPID(DWORD processId);
bool killName(string processName);

// ImageName
bool killName(string processName) {
    DWORD processId = findName(processName);
    return killPID(processId);
}

// PID
bool killPID(DWORD processId) {
    HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
    TerminateProcess(processHandle, 0);
    CloseHandle(processHandle);
    return true;
}

int main() {
    cout << "Name OR PID [n/p]: ";

    char luachon;
    cin >> luachon;

    luachon = (char) tolower(luachon);

    if (luachon == 'p') {
        DWORD processId;
        cout << "PID: ";
        cin >> processId;

        if (killPID(processId)) {
            cout << "Process with ID " << processId << " terminated successfully!" << endl;
        }
    } else if (luachon == 'n') {
        string processName;
        if (killName(processName)) {
            cout << "Process with name " << processName << " terminated successfully!" << endl;
        }
    }

    string ketthuc = "\nEnter a string to exit the program!\n";
    cout << ketthuc;
    cin >> ketthuc;
    return 0;
}