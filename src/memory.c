#include <stdio.h>
#include <string.h>
#include "memory.h"

/*
 * Reads memory info from /proc/meminfo.
 * Uses MemAvailable (not MemFree) for accurate real-world usage.
 * MemAvailable accounts for reclaimable cache/buffers, giving a
 * true picture of how much memory is actually free for applications.
 */
double get_memory_usage() {

    FILE *fp;
    char line[128];
    long total = -1, available = -1;

    fp = fopen("/proc/meminfo", "r");
    if (!fp) return -1;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "MemTotal:", 9) == 0)
            sscanf(line, "MemTotal: %ld kB", &total);
        else if (strncmp(line, "MemAvailable:", 13) == 0)
            sscanf(line, "MemAvailable: %ld kB", &available);

        if (total != -1 && available != -1)
            break;
    }

    fclose(fp);

    if (total <= 0 || available < 0) return -1;

    return 100.0 * (total - available) / total;
}