#include <iostream>
#include <filesystem>

using namespace std;

void ListFilesInDirectory(const std::filesystem::path& directory) {
    cout << directory.string() << endl;

    for (auto fileName : std::filesystem::directory_iterator(directory)) {
        cout << "|_ " << fileName.path().filename().string() << endl;
    }
}

int main() {
    std::filesystem::path directory = std::filesystem::current_path();

    ListFilesInDirectory(directory);

    string ketthuc = "\nPress any character + Enter to exit the program!\n";
    cout << ketthuc;
    cin >> ketthuc;
    return 0;
}
