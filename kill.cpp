#include <iostream>
#include <cstdlib>

int main() {
    system("taskkill /F /IM \"ReaderOn.exe\"");
    system("taskkill /F /IM \"NotepadPlus1.exe\"");
    std::cout << "Done." << std::endl;
    return 0;
}