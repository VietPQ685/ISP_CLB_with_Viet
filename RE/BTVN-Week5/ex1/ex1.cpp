#include <windows.h>
#include <bits/stdc++.h>
#include <string>

using namespace std;


std::wstring QueryRegistryValue(HKEY hKeyIn, LPCWSTR subKey, LPCWSTR lpvalueName) {
    HKEY hKey;
    DWORD dataSize;
    DWORD lpType = 0;
    wchar_t lpData[256] = { 0 };

    // Mở khóa Registry
    if (RegOpenKeyExW(hKeyIn, subKey, 0, KEY_READ, &hKey) == 0) {; // trả về giá trị là 0 nếu mở thành công
        // Lấy kích thước giá trị
        RegQueryValueExW(hKey, lpvalueName, nullptr, &lpType, nullptr, &dataSize);

        // Lấy giá trị
        RegQueryValueExW(hKey, lpvalueName, nullptr, &lpType, reinterpret_cast<LPBYTE>(lpData), &dataSize);
    }

    RegCloseKey(hKey);
    return std::wstring(lpData);
}


int main() {
    // Device Name
    std::wstring DeviceName = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"SystemVersion");
    std::wcout << L"Device Name: " << DeviceName << endl;

    // Host Name
    std::wstring HostName = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ActiveComputerName", L"ComputerName");
    std::wcout << L"Host Name: " << HostName << endl;

    // OS Name
    std::wstring OSName = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName");
    std::wcout << L"OS Name: " << OSName << endl;

    // OS Version
    std::wstring OSVersion = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"CurrentVersion");
    std::wcout << L"OS Version: " << OSVersion << endl;

    // OS BuildType
    std::wstring OSBuildType = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"CurrentType");
    std::wcout << L"OS BuildType: " << OSBuildType << endl;


    string ketthuc = "\nPress any character + Enter to exit the program!\n";
    cout << ketthuc;
    cin >> ketthuc;
    return 0;
}