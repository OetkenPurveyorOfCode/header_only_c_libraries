#ifndef PROCESSLIST_H
#define PROCESSLIST_H
#include <windows.h>
#include <psapi.h>

/// @brief Returns the name of the process with PID
/// @param pid PID
/// @param out_name buffer to fill with the name
/// @param out_len available memory to fill
/// @return length of the name, 0 indicates failure
size_t psl_processname(DWORD pid, char* out_name, size_t out_len);

/// @brief Get all the PIDs of all processes
/// @param pids 
/// @param pids_len 
/// @return number of processes
size_t psl_enumerate(DWORD pids[], size_t pids_len);

#endif // PROCESSLIST_H
//////////////////////////////////////////////////////////
#if defined(PSLIST_IMPLEMENTATION) || defined(UNITY_BUILD)
size_t psl_enumerate(DWORD pids[], size_t pids_len) {
    DWORD needed;
    if(EnumProcesses(pids, pids_len, &needed)) {
        return (size_t)needed;
    } else {
        return 0;
    }
}

size_t psl_processname(DWORD pid, char* out_name, size_t out_len) {
    HANDLE process = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        pid
    );
    if (process == NULL) {
        return 0;
    }
    HMODULE module;
    DWORD needed;
    if (!EnumProcessModules(process, &module, sizeof(module), &needed) )
    {
        return 0;
    }
    (void)needed;
    return GetModuleBaseNameA(process, module, out_name, out_len);
}
#endif
