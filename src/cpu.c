#include <stdio.h>
#include <unistd.h>
#include "cpu.h"

double get_cpu_usage(){

    FILE* fp;
    // opening /proc/stat (linux)

    unsigned long long user1, nice1, system1, idle1;
    unsigned long long user2, nice2, system2, idle2;

    unsigned long long total1, total2;
    unsigned long long total_diff, idle_diff;

    // 1st read 
    fp = fopen("/proc/stat", "r");
    if (!fp) return -1; 

    fscanf(fp, "cpu  %llu %llu %llu %llu", &user1, &nice1, &system1, &idle1);

    fclose(fp);

    sleep(1);

    // 2nd read
    fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    fscanf(fp, "cpu  %llu %llu %llu %llu", &user2, &nice2, &system2, &idle2);
    
    fclose(fp);

    total1 = user1 + nice1 + system1 + idle1;
    total2 = user2 + nice2 + system2 + idle2;

    total_diff = total2 - total1;
    idle_diff = idle2 - idle1;

    return 100.0 * (total_diff - idle_diff) / total_diff;

}