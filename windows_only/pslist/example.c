#include <stdio.h>
#include <stdlib.h>
#define PSLIST_IMPLEMENTATION
#include "pslist.h"


int main(void) {
    DWORD pids[4096];
    size_t num_procs = psl_enumerate(pids, sizeof(pids));
    if (num_procs == 0) {
        fprintf(stderr, "Failed!\n");
        return -1;
    }
    for (size_t i = 0; i < num_procs; i++) {
        char name[1024];
        DWORD pid = pids[i];
        size_t num = psl_processname(pid, name, sizeof(name));
        if (num) printf("name: %s, pid: %lu\n", name, pid);
    }
    printf("%zu processes\n", num_procs);
    return 0;
}
