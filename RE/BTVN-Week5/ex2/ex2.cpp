#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

void ListMemoryRegions(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T address = 0;

    cout << "Memory regions with PAGE_EXECUTE_READWRITE in PID " << processID << ":" << endl;

    while (VirtualQueryEx(hProcess, (LPCVOID)address, &mbi, sizeof(mbi))) {
        if (mbi.Protect == PAGE_EXECUTE_READWRITE) {
            cout << "Address: " << mbi.BaseAddress << endl;
        }
        address += mbi.RegionSize;
    }

    CloseHandle(hProcess);
}

int main() {

    cout << "PID: ";
    DWORD processID;
    cin >> processID;
    ListMemoryRegions(processID);

    return 0;
}