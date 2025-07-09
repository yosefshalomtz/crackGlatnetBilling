#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>

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

void try_WinApiKillProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    
    // Take a snapshot of all processes in the system
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to create process snapshot.\n");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    // Retrieve information about the first process
    if (!Process32First(hProcessSnap, &pe32)) {
        fprintf(stderr, "Failed to get first process.\n");
        CloseHandle(hProcessSnap);
        return;
    }

    HANDLE ReaderOnProcess = NULL;
    HANDLE NotepadPlus1Process = NULL;

    do {
        if (strcmp(pe32.szExeFile, "ReaderOn.exe") == 0)
            ReaderOnProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
        else if(strcmp(pe32.szExeFile, "NotepadPlus1.exe") == 0)
            NotepadPlus1Process = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));

    if(ReaderOnProcess != NULL) {
        TerminateProcess(ReaderOnProcess, 0);
        CloseHandle(ReaderOnProcess);
        printf("ReaderOn.exe process terminated successfully.\n");
    } else {
        fprintf(stderr, "Failed to find ReaderOn.exe process.\n");
    }
    if(NotepadPlus1Process != NULL) {
        TerminateProcess(NotepadPlus1Process, 0);
        CloseHandle(NotepadPlus1Process);
        printf("NotepadPlus1.exe process terminated successfully.\n");
    } else {
        fprintf(stderr, "Failed to find NotepadPlus1.exe process.\n");
    }

    CloseHandle(hProcessSnap);
}

int main() {
    // the simple way:
    printf("1. system command...\n");
    system("taskkill /F /IM \"ReaderOn.exe\"");
    system("taskkill /F /IM \"NotepadPlus1.exe\"");
    // another way:
    printf("2. Executing powershell...\n");
    try_launch_powershell();
    // one more way:
    printf("3. Executing WinAPI...\n");
    try_WinApiKillProcesses();
    printf("Done.\n");
    return 0;
}