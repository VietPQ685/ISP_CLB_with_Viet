#include <windows.h>
#include <tlhelp32.h>
#include <bits/stdc++.h>
#include <string>

using namespace std;

void inkytu(string s, int k) {
    for (int i = 0; i < k; i++) {
        cout << s;
    }
}

int main() {
    HANDLE allProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // Lấy snapshot của tất cả các tiến trình đang chạy
    PROCESSENTRY32 pe32;

    // Bắt đầu liệt kê các tiến trình
    int tong_kc_name = 50;

    cout << "Process Name";
    inkytu(" ", tong_kc_name + 1 - 12);
    cout << "PID\n";

    inkytu("#", tong_kc_name);
    cout << " ";
    inkytu("#", 10);
    cout << "\n\n";
    
    while (Process32Next(allProcess, &pe32)) { // In ra Image Name và số PID
        string name = pe32.szExeFile;
        int id = pe32.th32ProcessID;

        cout << name;
        inkytu(" ", tong_kc_name + 1 - name.size());
        cout << id << endl;
    }

    CloseHandle(allProcess); // Đóng handle snapshot sau khi đã sử dụng xong

    string ketthuc = "\nPress any character + Enter to exit the program!\n";
    cout << ketthuc;
    cin >> ketthuc;
    return 0;
}
