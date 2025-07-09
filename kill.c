#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void try_launch_powershell() { 
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    const char* exe = "C://Windows//System32//WindowsPowerShell//v1.0//powershell.exe";
    char* cmd = "\"C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe\" -Command \"taskkill /F /IM 'ReaderOn.exe'; taskkill /F /IM 'NotepadPlus1.exe'\"";
    if (!CreateProcessA(exe, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        fprintf(stderr, "Failed to launch PowerShell.\n");
    else {
        // wait for the process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

int main() {
    /**
    // the simple way:
    system("taskkill /F /IM \"ReaderOn.exe\"");
    system("taskkill /F /IM \"NotepadPlus1.exe\"");
    */
    // another way:
    printf("Executing powershell...\n");
    try_launch_powershell();
    printf("Done.\n");
    return 0;
}