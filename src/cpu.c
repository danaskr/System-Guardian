#include <stdio.h>
#include <unistd.h>
#include "cpu.h"
#include "config.h"

/*
 * Reads all 10 fields from /proc/stat for accurate CPU usage.
 * Takes two samples separated by MONITOR_INTERVAL and calculates
 * the percentage of time the CPU was not idle between them.
 *
 * Fields: user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice
 */
double get_cpu_usage() {

    FILE *fp;

    unsigned long long user1, nice1, system1, idle1, iowait1, irq1, softirq1, steal1;
    unsigned long long user2, nice2, system2, idle2, iowait2, irq2, softirq2, steal2;

    unsigned long long total1, total2, idle_total1, idle_total2;
    unsigned long long total_diff, idle_diff;

    // 1st sample
    fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    fscanf(fp, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu",
           &user1, &nice1, &system1, &idle1,
           &iowait1, &irq1, &softirq1, &steal1);
    fclose(fp);

    sleep(MONITOR_INTERVAL);

    // 2nd sample
    fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    fscanf(fp, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu",
           &user2, &nice2, &system2, &idle2,
           &iowait2, &irq2, &softirq2, &steal2);
    fclose(fp);

    // idle includes iowait (time waiting for I/O counts as idle in usage terms)
    idle_total1 = idle1 + iowait1;
    idle_total2 = idle2 + iowait2;

    total1 = user1 + nice1 + system1 + idle1 + iowait1 + irq1 + softirq1 + steal1;
    total2 = user2 + nice2 + system2 + idle2 + iowait2 + irq2 + softirq2 + steal2;

    total_diff = total2 - total1;
    idle_diff  = idle_total2 - idle_total1;

    if (total_diff == 0) return 0.0;

    return 100.0 * (total_diff - idle_diff) / total_diff;
}