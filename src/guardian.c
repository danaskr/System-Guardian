#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define CPU_THRESHOLD 80.0
#include "cpu.h"
#include "memory.h"

int main() {

    while (1) {
        double cpu = get_cpu_usage(); 
        double mem = get_memory_usage();

        printf("CPU : %.2f%%, Memory : %.2f%%\n", cpu, mem);
        sleep(2);

        if (cpu > CPU_THRESHOLD) {
            printf("ALERT: High CPU Usage!\n");
        }
    }

    return 0;
}