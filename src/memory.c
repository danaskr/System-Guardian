#include <stdio.h>
#include "memory.h"

double get_memory_usage() {

    FILE* fp;
    long total = 0, free = 0;

    fp = fopen("/proc/meminfo", "r");
    if (!fp) return -1;

    fscanf(fp, "MemTotal: %ld kB\n", &total);
    fscanf(fp, "MemFree: %ld kB\n", &free);

    fclose(fp);

    return 100.0 * (total - free) / total;
}