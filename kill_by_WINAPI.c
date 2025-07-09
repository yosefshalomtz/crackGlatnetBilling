#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>

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
    printf("Executing WinAPI...\n");
    try_WinApiKillProcesses();
    printf("Done.\n");
    return 0;
}